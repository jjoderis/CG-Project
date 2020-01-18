#include <OpenGL/scene/OpenGLScene.h>
#include <OpenGL/geometry/OpenGLGeometry.h>
#include <OpenGL/material/OpenGLMaterial.h>

void setUpBox(CG::OpenGLScene &scene){
    std::shared_ptr<CG::OpenGLGeometry> boxPtr = std::make_shared<CG::OpenGLGeometry>(CG::OpenGLGeometry{
        {
            { -5.0, -5.0, 5.0 },
            {  5.0, -5.0, 5.0 },
            { -5.0, -5.0, 5.0 },
            { -5.0,  5.0, 5.0 },
            {  5.0, -5.0, 5.0 },
            {  5.0,  5.0, 5.0 },
            { -5.0,  5.0, 5.0 },
            {  5.0,  5.0, 5.0 },
            
            { -5.0, -5.0, -5.0 },
            {  5.0, -5.0, -5.0 },
            { -5.0, -5.0, -5.0 },
            { -5.0,  5.0, -5.0 },
            {  5.0, -5.0, -5.0 },
            {  5.0,  5.0, -5.0 },
            { -5.0,  5.0, -5.0 },
            {  5.0,  5.0, -5.0 },

            { -5.0, -5.0, -5.0 },
            { -5.0, -5.0,  5.0 },
            {  5.0, -5.0, -5.0 },
            {  5.0, -5.0,  5.0 },
            { -5.0,  5.0, -5.0 },
            { -5.0,  5.0,  5.0 },
            {  5.0,  5.0, -5.0 },
            {  5.0,  5.0,  5.0 }
        },
        {}
    });
    std::shared_ptr<CG::OpenGLMaterial> yellowPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{CG::RGBA_Color{1.0, 1.0, 0.0, 1.0}});
    std::shared_ptr<CG::OpenGLMesh> yellowCube{new CG::OpenGLMesh{boxPtr, yellowPtr}};

    yellowPtr->setDrawMode(GL_LINES);
    yellowCube->setRenderFunction([](CG::OpenGLMesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 & projectionMatrix){
        std::shared_ptr<CG::OpenGLMaterial> material{ mesh->getMaterial() };
        std::shared_ptr<CG::OpenGLGeometry> geometry{ mesh->getGeometry() }; 

        CG::Matrix4 modelViewMatrix{dot(viewMatrix, mesh->getMatrixWorld())};
        //transpose inverse of modelView Matrix N = ((mV)^-1)^T = ((V * M)^-1)^T = (M^-1 * V^-1)^T
        
        CG::Matrix4 normalMatrix{dot(mesh->getMatrixWorldInverse(), viewMatrixInverse).transpose()};

        glUseProgram(material->getProgram());

        glUniform4fv(material->uniformLocs.baseColor, 1, material->getColor().data());
        glUniformMatrix4fv(material->uniformLocs.modelMatrix, 1, GL_FALSE, mesh->getMatrixWorld().data());
        glUniformMatrix4fv(material->uniformLocs.viewMatrix, 1, GL_FALSE, viewMatrix.data());
        glUniformMatrix4fv(material->uniformLocs.modelViewMatrix, 1, GL_FALSE, modelViewMatrix.data());
        glUniformMatrix4fv(material->uniformLocs.projectionMatrix, 1, GL_FALSE, projectionMatrix.data());
        glUniformMatrix4fv(material->uniformLocs.normalMatrix, 1, GL_FALSE, normalMatrix.data());
        glUniform1f(material->uniformLocs.shininess, material->getShininess());

        glBindVertexArray(geometry->getVAO());
        glDrawArrays(GL_LINES, 0, geometry->getNumVertices());

        for(const std::shared_ptr<CG::OpenGLMesh> &child : mesh->getChildren()){
            child->render(viewMatrix, viewMatrixInverse, projectionMatrix);
        }
    });

    scene.addChild(yellowCube);
}