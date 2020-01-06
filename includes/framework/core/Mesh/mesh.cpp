#include "mesh.h"

CG::Mesh::Mesh() : Object3D() {}

CG::Mesh::Mesh(const CG::Geometry &geometry, const CG::Material &material) 
    : Object3D(),
      m_geometry(std::make_shared<CG::Geometry>(geometry)),
      m_material(std::make_shared<CG::Material>(material))
{}

CG::Mesh::Mesh(const std::shared_ptr<CG::Geometry> &geometry, const std::shared_ptr<CG::Material> &material)
    : Object3D(),
      m_geometry{ geometry },
      m_material{ material }
{}

CG::Mesh::Mesh(const Mesh &other)
    : Object3D(other),
      m_geometry(other.m_geometry),
      m_material(other.m_material)
{}

CG::Mesh& CG::Mesh::operator= (const CG::Mesh &other){

    if(&other == this){
        return *this;
    }

    m_geometry = other.m_geometry;
    m_material = other.m_material;
    m_position = other.m_position;

    return *this;
}

void CG::Mesh::setGeometry(const CG::Geometry &geometry){
    m_geometry = std::make_shared<CG::Geometry>(geometry);
}

void CG::Mesh::setGeometry(const std::shared_ptr<CG::Geometry> &geometry){
    m_geometry = geometry;
}

std::shared_ptr<CG::Geometry>& CG::Mesh::getGeometry(){
    return m_geometry;
}

void CG::Mesh::setMaterial(const CG::Material &material){
    m_material = std::make_shared<CG::Material>(material);
}

void CG::Mesh::setMaterial(const std::shared_ptr<CG::Material> &material){
    m_material = material;
}

std::shared_ptr<CG::Material>& CG::Mesh::getMaterial(){
    return m_material;
}

void CG::Mesh::render(){

    if(!m_geometry || !m_material){
        return;
    }

    m_material->use();
    
    glUniformMatrix4fv(m_material->uniformLocs.worldMatrix, 1, GL_FALSE, m_worldMatrix.data());

    m_geometry->draw();
}