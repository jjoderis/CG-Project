#include "renderer.h"
#include <memory>

void CG::Renderer::renderMesh(const Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix) const{
    std::shared_ptr<Material> material{mesh->getMaterial()};
    std::shared_ptr<Geometry> geometry{mesh->getGeometry()};
    
    Matrix4 modelViewMatrix{dot(viewMatrix, mesh->getMatrixWorld())};
    //transpose inverse of modelView Matrix N = ((mV)^-1)^T = ((V * M)^-1)^T = (M^-1 * V^-1)^T
    
    Matrix4 normalMatrix{dot(mesh->getMatrixWorldInverse(), viewMatrixInverse).transpose()};

    glUseProgram(material->getProgram());

    glUniform4fv(material->uniformLocs.baseColor, 1, material->getColor().data());
    glUniformMatrix4fv(material->uniformLocs.modelViewMatrix, 1, GL_FALSE, modelViewMatrix.data());
    glUniformMatrix4fv(material->uniformLocs.projectionMatrix, 1, GL_FALSE, projectionMatrix.data());
    glUniformMatrix4fv(material->uniformLocs.normalMatrix, 1, GL_FALSE, normalMatrix.data());

    glBindVertexArray(geometry->getVAO());
    if(geometry->getNumFaces()){
        glDrawElements(m_drawMode, 3 * geometry->getNumFaces(), GL_UNSIGNED_INT, NULL);
    }else{
        glDrawArrays(m_drawMode, 0, geometry->getNumVertices());
    }

    for(const std::shared_ptr<Mesh> &child : mesh->getChildren()){
        renderMesh(child.get(), viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}

void CG::Renderer::render(const Scene &scene, const Camera &camera) const{
    glClearBufferfv(GL_COLOR, 0, scene.getBackground().data());
    
    Matrix4 viewMatrix = camera.getMatrixWorldInverse();
    Matrix4 viewMatrixInverse = camera.getMatrixWorld();
    Matrix4 projectionMatrix = camera.getProjectionMatrix(); 

    for(const std::shared_ptr<Mesh> &mesh : scene.getChildren()){
        renderMesh(mesh.get(), viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}