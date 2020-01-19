#include <OpenGL/scene/OpenGLScene.h>
#include <OpenGL/geometry/OpenGLGeometry.h>
#include <OpenGL/material/OpenGLMaterial.h>

void setUpBoxGeometry(CG::OpenGLMesh *mesh){
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

    mesh->setGeometry(boxPtr);
}

void setUpYellowMaterial(CG::OpenGLMesh *mesh){
    std::shared_ptr<CG::OpenGLMaterial> yellowPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{CG::RGBA_Color{1.0, 1.0, 0.0, 1.0}});

    yellowPtr->addUniform("modelViewMatrix");
    yellowPtr->addUniform("projectionMatrix");
    yellowPtr->addUniform("normalMatrix");
    yellowPtr->addUniform("viewMatrix");
    yellowPtr->addUniform("baseColor");
    yellowPtr->addUniform("shininess");
    yellowPtr->addUniform("modelMatrix");

    mesh->setMaterial(yellowPtr);
}

void setUpBox(CG::OpenGLScene &scene){
    
    
    std::shared_ptr<CG::OpenGLMesh> yellowCube{new CG::OpenGLMesh{}};

    setUpBoxGeometry(yellowCube.get());
    setUpYellowMaterial(yellowCube.get());


    yellowCube->setRenderFunction([](CG::OpenGLMesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 & projectionMatrix){
        std::shared_ptr<CG::OpenGLMaterial> material{ mesh->getMaterial() };
        std::shared_ptr<CG::OpenGLGeometry> geometry{ mesh->getGeometry() }; 

        CG::Matrix4 modelViewMatrix{dot(viewMatrix, mesh->getMatrixWorld())};
        //transpose inverse of modelView Matrix N = ((mV)^-1)^T = ((V * M)^-1)^T = (M^-1 * V^-1)^T
        
        CG::Matrix4 normalMatrix{dot(mesh->getMatrixWorldInverse(), viewMatrixInverse).transpose()};

        glUseProgram(material->getProgram());

        glUniform4fv(material->uniforms.at("baseColor"), 1, material->getColor().data());
        glUniformMatrix4fv(material->uniforms.at("modelMatrix"), 1, GL_FALSE, mesh->getMatrixWorld().data());
        glUniformMatrix4fv(material->uniforms.at("viewMatrix"), 1, GL_FALSE, viewMatrix.data());
        glUniformMatrix4fv(material->uniforms.at("modelViewMatrix"), 1, GL_FALSE, modelViewMatrix.data());
        glUniformMatrix4fv(material->uniforms.at("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
        glUniformMatrix4fv(material->uniforms.at("normalMatrix"), 1, GL_FALSE, normalMatrix.data());
        glUniform1f(material->uniforms.at("shininess"), material->getShininess());

        glBindVertexArray(geometry->getVAO());
        glDrawArrays(GL_LINES, 0, geometry->getNumVertices());
    });

    scene.addChild(yellowCube);
}