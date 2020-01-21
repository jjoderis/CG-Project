#ifndef CG_SETUP_RENDERFUNC_H
#define CG_SETUP_RENDERFUNC_H

#include <OpenGL/mesh/OpenGLMesh.h>
#include <OpenGL/geometry/OpenGLGeometry.h>
#include <OpenGL/material/OpenGLMaterial.h>

void setUpPlainRendering(CG::OpenGLMesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 & projectionMatrix){
    std::shared_ptr<CG::OpenGLMaterial> material{ mesh->getMaterial() };
    std::shared_ptr<CG::OpenGLGeometry> geometry{ mesh->getGeometry() }; 

    CG::Matrix4 modelViewMatrix{ viewMatrix * mesh->getMatrixWorld() };
    //transpose inverse of modelView Matrix N = ((mV)^-1)^T = ((V * M)^-1)^T = (M^-1 * V^-1)^T
    
    CG::Matrix4 normalMatrix{(mesh->getMatrixWorldInverse() * viewMatrixInverse).transpose()};

    glUseProgram(material->getProgram());

    glUniform4fv(material->uniforms.at("baseColor"), 1, material->getColor().data());
    glUniformMatrix4fv(material->uniforms.at("modelViewMatrix"), 1, GL_FALSE, modelViewMatrix.data());
    glUniformMatrix4fv(material->uniforms.at("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());

    glBindVertexArray(geometry->getVAO());
}

void renderPlainWireFrame(CG::OpenGLMesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 & projectionMatrix){
    std::shared_ptr<CG::OpenGLGeometry> geometry{ mesh->getGeometry() }; 

    setUpPlainRendering(mesh, viewMatrix, viewMatrixInverse, projectionMatrix);

    glDrawArrays(GL_LINES, 0, geometry->getNumVertices());

    for(const std::shared_ptr<CG::OpenGLMesh> &child : mesh->getChildren()){
        child->render(viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}

void renderPlainSolid(CG::OpenGLMesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 & projectionMatrix){
    std::shared_ptr<CG::OpenGLGeometry> geometry{ mesh->getGeometry() }; 

    setUpPlainRendering(mesh, viewMatrix, viewMatrixInverse, projectionMatrix);

    glDrawElements(GL_TRIANGLES, 3 * geometry->getNumFaces(), GL_UNSIGNED_INT, NULL);

    for(const std::shared_ptr<CG::OpenGLMesh> &child : mesh->getChildren()){
        child->render(viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}

void renderPhong(CG::OpenGLMesh *mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 & projectionMatrix){
    std::shared_ptr<CG::OpenGLMaterial> material{ mesh->getMaterial() };
    std::shared_ptr<CG::OpenGLGeometry> geometry{ mesh->getGeometry() }; 

    CG::Matrix4 modelViewMatrix{ viewMatrix * mesh->getMatrixWorld() };
    //transpose inverse of modelView Matrix N = ((mV)^-1)^T = ((V * M)^-1)^T = (M^-1 * V^-1)^T
    
    CG::Matrix4 normalMatrix{(mesh->getMatrixWorldInverse() * viewMatrixInverse).transpose()};

    glUseProgram(material->getProgram());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, material->getTextures()[0]);

    glUniform4fv(material->uniforms.at("baseColor"), 1, material->getColor().data());
    glUniformMatrix4fv(material->uniforms.at("modelMatrix"), 1, GL_FALSE, mesh->getMatrixWorld().data());
    glUniformMatrix4fv(material->uniforms.at("viewMatrix"), 1, GL_FALSE, viewMatrix.data());
    glUniformMatrix4fv(material->uniforms.at("modelViewMatrix"), 1, GL_FALSE, modelViewMatrix.data());
    glUniformMatrix4fv(material->uniforms.at("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
    glUniformMatrix4fv(material->uniforms.at("normalMatrix"), 1, GL_FALSE, normalMatrix.data());
    glUniform1f(material->uniforms.at("shininess"), material->getShininess());

    glBindVertexArray(geometry->getVAO());
    glDrawElements(GL_TRIANGLES, 3 * geometry->getNumFaces(), GL_UNSIGNED_INT, NULL);
    

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    for(const std::shared_ptr<CG::OpenGLMesh> &child : mesh->getChildren()){
        child->render(viewMatrix, viewMatrixInverse, projectionMatrix);
    }
}

#endif