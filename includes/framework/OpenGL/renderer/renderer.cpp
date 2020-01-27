#include "renderer.h"

CG::Renderer::Renderer(){
    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT, GL_FILL);
    // glPolygonMode(GL_BACK, GL_LINE);
}

void CG::renderScene(CG::Renderer &renderer, CG::OpenGLScene &scene, CG::Camera &camera){
    (void)renderer;

    glClearBufferfv(GL_COLOR, 0, scene.getBackground().data());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix4 viewMatrix = camera.getMatrixWorldInverse();
    Matrix4 viewMatrixInverse = camera.getMatrixWorld();
    Matrix4 projectionMatrix = camera.getProjectionMatrix();

    for(const std::shared_ptr<CG::OpenGLMesh> &mesh : scene.getChildren()){

        if(mesh->isAnimated){
            mesh->animate();
        }

        mesh->render(viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}

void CG::Renderer::render(CG::OpenGLScene &scene, CG::Camera &camera){
    m_renderFunction(*this, scene, camera);
}

void CG::Renderer::setDrawMode(GLenum drawMode){
    m_drawMode = drawMode;
}
inline GLenum CG::Renderer::getDrawMode() const{
    return m_drawMode;
}

std::vector<unsigned int>& CG::Renderer::getTransformFeedbacks(){
    return m_tranformFeedbacks;
}

void CG::Renderer::setRenderFunction(void(*renderFunction)(Renderer &renderer, OpenGLScene &scene, Camera &camera)){
    m_renderFunction = renderFunction;
}

void CG::Renderer::increaseFrameCounter(){
    ++m_frameCounter;
}
void CG::Renderer::setFrameCounter(int count){
    m_frameCounter = count; 
}
int CG::Renderer::getFrameCount(){
    return m_frameCounter;
}
