#include "renderer.h"
#include <memory>

CG::Renderer::Renderer(){
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
}

void CG::renderMesh(Renderer &renderer, const Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){
    std::shared_ptr<OpenGLMaterial> material{ std::dynamic_pointer_cast<OpenGLMaterial>(mesh->getMaterial()) };
    std::shared_ptr<OpenGLGeometry> geometry{ std::dynamic_pointer_cast<OpenGLGeometry>(mesh->getGeometry()) }; 

    Matrix4 modelViewMatrix{dot(viewMatrix, mesh->getMatrixWorld())};
    //transpose inverse of modelView Matrix N = ((mV)^-1)^T = ((V * M)^-1)^T = (M^-1 * V^-1)^T
    
    Matrix4 normalMatrix{dot(mesh->getMatrixWorldInverse(), viewMatrixInverse).transpose()};

    glUseProgram(material->getProgram());

    glUniform4fv(material->uniformLocs.baseColor, 1, material->getColor().data());
    glUniformMatrix4fv(material->uniformLocs.modelMatrix, 1, GL_FALSE, mesh->getMatrixWorld().data());
    glUniformMatrix4fv(material->uniformLocs.viewMatrix, 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(material->uniformLocs.modelViewMatrix, 1, GL_FALSE, modelViewMatrix.data());
    glUniformMatrix4fv(material->uniformLocs.projectionMatrix, 1, GL_FALSE, projectionMatrix.data());
    glUniformMatrix4fv(material->uniformLocs.normalMatrix, 1, GL_FALSE, normalMatrix.data());
    glUniform1f(material->uniformLocs.shininess, material->getShininess());

    glBindVertexArray(geometry->getVAO());
    if(geometry->getNumFaces()){
        glDrawElements(material->getDrawMode(), 3 * geometry->getNumFaces(), GL_UNSIGNED_INT, NULL);
    }else{
        glDrawArrays(material->getDrawMode(), 0, geometry->getNumVertices());
    }

    for(const std::shared_ptr<Mesh> &child : mesh->getChildren()){
        renderMesh(renderer, child.get(), viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}

void CG::renderScene(CG::Renderer &renderer, CG::Scene &scene, CG::Camera &camera){
    glClearBufferfv(GL_COLOR, 0, scene.getBackground().data());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix4 viewMatrix = camera.getMatrixWorldInverse();
    Matrix4 viewMatrixInverse = camera.getMatrixWorld();
    Matrix4 projectionMatrix = camera.getProjectionMatrix();

    for(const std::shared_ptr<Mesh> &mesh : scene.getChildren()){

        if(mesh->isAnimated){
            mesh->animate();
        }

        renderMesh(renderer, mesh.get(), viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}

void CG::Renderer::render(CG::Scene &scene, CG::Camera &camera){
    m_renderFunction(*this, scene, camera);
}

void CG::Renderer::setDrawMode(GLenum drawMode){
    m_drawMode = drawMode;
}
inline GLenum CG::Renderer::getDrawMode() const{
    return m_drawMode;
}

inline unsigned int& CG::Renderer::getTransformFeedback(){
    return m_tranformFeedback;
}

void CG::Renderer::setRenderFunction(void(*renderFunction)(Renderer &renderer, Scene &scene, Camera &camera)){
    m_renderFunction = renderFunction;
}
