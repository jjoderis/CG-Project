#include "OpenGLMesh.h"
#include <core/mesh/mesh.cpp>

template class CG::Mesh<CG::OpenGLGeometry, CG::OpenGLMaterial>;

template<>
void CG::Mesh<CG::OpenGLGeometry, CG::OpenGLMaterial>::render(const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){

    CG::Matrix4 modelViewMatrix{ viewMatrix * m_worldMatrix };
    //transpose inverse of modelView Matrix N = ((mV)^-1)^T = ((V * M)^-1)^T = (M^-1 * V^-1)^T
    
    CG::Matrix4 normalMatrix{(m_worldMatrixInverse * viewMatrixInverse).transpose()};

    glUseProgram(m_material->getProgram());
    m_material->bindTextures();
    m_material->setupUniformData();

    
    glUniformMatrix4fv(m_material->getUniform("modelMatrix"), 1, GL_FALSE, m_worldMatrix.data());
    glUniformMatrix4fv(m_material->getUniform("viewMatrix"), 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(m_material->getUniform("modelViewMatrix"), 1, GL_FALSE, modelViewMatrix.data());
    glUniformMatrix4fv(m_material->getUniform("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
    glUniformMatrix4fv(m_material->getUniform("normalMatrix"), 1, GL_FALSE, normalMatrix.data());

    beforeRender(*this, viewMatrix, viewMatrixInverse, projectionMatrix);

    m_geometry->drawGeometry();

    afterRender(*this, viewMatrix, viewMatrixInverse, projectionMatrix);
    
    m_material->unbindTextures();

    for(const std::shared_ptr<CG::OpenGLMesh> &child : m_children){
        child->render(viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}