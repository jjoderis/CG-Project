#include "renderer.h"

CG::Renderer::Renderer(int width, int height) : m_screenWidth{ width }, m_screenHeight{ height }{
    glEnable(GL_DEPTH_TEST);
    
    glGenTextures(1, &m_depthTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_depthTexture);

    for (int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT32, m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glGenFramebuffers(1, &m_depthFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_depthFBO);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthTexture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    std::vector<CG::ShaderInfo> shaderData{
        CG::ShaderInfo{ GL_VERTEX_SHADER, "../media/shaders/shadowPass/shadow.vert", true, 0 },
        CG::ShaderInfo{ GL_GEOMETRY_SHADER, "../media/shaders/shadowPass/shadow.geom", true, 0 },
        CG::ShaderInfo{ GL_FRAGMENT_SHADER, "../media/shaders/shadowPass/shadow.frag", true, 0 }
    };

    m_shadowProgram = CG::createShaderProgram(shaderData);
}

void renderMesh();

void CG::Renderer::render(CG::OpenGLScene &scene, CG::Camera &camera){

    // update all lights
    for(const std::shared_ptr<CG::Light> &light: scene.getLights()){
        if(light->isAnimated){
            light->animate();
        }
    }

    glViewport(0,0, m_shadowWidth, m_shadowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, m_depthFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glUseProgram(m_shadowProgram);
    // TODO: implement shadow pass
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport( 0, 0, m_screenWidth, m_screenHeight);
    glClearBufferfv(GL_COLOR, 0, scene.getBackground().data());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix4 viewMatrix = camera.getMatrixWorldInverse();
    Matrix4 viewMatrixInverse = camera.getMatrixWorld();
    Matrix4 projectionMatrix = camera.getProjectionMatrix();

    for(const std::shared_ptr<CG::OpenGLMesh> &mesh : scene.getChildren()){

        if(mesh->isAnimated){
            mesh->animate();
        }

        renderMesh(*mesh.get(), viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}

void CG::Renderer::renderMesh(OpenGLMesh &mesh, Matrix4 &viewMatrix, Matrix4 &viewMatrixInverse, Matrix4 &projectionMatrix){

    CG::Matrix4 worldMatrix{ mesh.getMatrixWorld() };
    CG::Matrix4 worldMatrixInverse{ mesh.getMatrixWorldInverse() };
    CG::OpenGLMaterial *material{ mesh.getMaterial().get() };
    CG::OpenGLGeometry *geometry{ mesh.getGeometry().get() };

    CG::Matrix4 modelViewMatrix{ viewMatrix * worldMatrix };
    //transpose inverse of modelView Matrix N = ((mV)^-1)^T = ((V * M)^-1)^T = (M^-1 * V^-1)^T
    
    CG::Matrix4 normalMatrix{(worldMatrixInverse * viewMatrixInverse).transpose()};

    CG::Matrix4 MVPMatrix{ projectionMatrix * modelViewMatrix };

    glUseProgram(material->getProgram());
    material->bindTextures();
    material->setupUniformData();

    
    glUniformMatrix4fv(material->getUniform("modelMatrix"), 1, GL_FALSE, worldMatrix.data());
    glUniformMatrix4fv(material->getUniform("viewMatrix"), 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(material->getUniform("viewMatrixInverse"), 1, GL_FALSE, viewMatrixInverse.data());
    glUniformMatrix4fv(material->getUniform("modelViewMatrix"), 1, GL_FALSE, modelViewMatrix.data());
    glUniformMatrix4fv(material->getUniform("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
    glUniformMatrix4fv(material->getUniform("normalMatrix"), 1, GL_FALSE, normalMatrix.data());
    glUniformMatrix4fv(material->getUniform("MVPMatrix"), 1, GL_FALSE, MVPMatrix.data());

    mesh.beforeRender(mesh, viewMatrix, viewMatrixInverse, projectionMatrix);

    geometry->drawGeometry();

    mesh.afterRender(mesh, viewMatrix, viewMatrixInverse, projectionMatrix);
    
    material->unbindTextures();

    for(const std::shared_ptr<CG::OpenGLMesh> &child : mesh.getChildren()){
        renderMesh(*child.get(), viewMatrix, viewMatrixInverse, projectionMatrix);
    }
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

void CG::Renderer::increaseFrameCounter(){
    ++m_frameCounter;
}
void CG::Renderer::setFrameCounter(int count){
    m_frameCounter = count; 
}
int CG::Renderer::getFrameCount(){
    return m_frameCounter;
}
