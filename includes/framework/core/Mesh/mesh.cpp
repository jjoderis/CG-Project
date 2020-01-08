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
      m_material(other.m_material),
      m_parent{ other.m_parent},
      m_children{other.m_children}
{}

CG::Mesh& CG::Mesh::operator= (const CG::Mesh &other){

    if(&other == this){
        return *this;
    }

    m_geometry = other.m_geometry;
    m_material = other.m_material;
    m_position = other.m_position;

    m_parent = other.m_parent;
    m_children = other.m_children;

    return *this;
}

void CG::Mesh::updateMatrixWorld() {
    CG::Object3D::updateMatrixWorld();

    if(m_parent.lock()){
        m_worldMatrix = dot(m_parent.lock()->m_worldMatrix, m_worldMatrix);
        m_worldMatrixInverse = dot(m_worldMatrixInverse, m_parent.lock()->m_worldMatrixInverse);
    }

    for(unsigned int i = 0; i < m_children.size(); ++i){
        m_children[i]->updateMatrixWorld();
    }
}

void CG::Mesh::setGeometry(const CG::Geometry &geometry){
    m_geometry = std::make_shared<CG::Geometry>(geometry);
}

void CG::Mesh::setGeometry(const std::shared_ptr<CG::Geometry> &geometry){
    m_geometry = geometry;
}

std::shared_ptr<CG::Geometry> CG::Mesh::getGeometry() const{
    return m_geometry;
}

void CG::Mesh::setMaterial(const CG::Material &material){
    m_material = std::make_shared<CG::Material>(material);
}

void CG::Mesh::setMaterial(const std::shared_ptr<CG::Material> &material){
    m_material = material;
}

std::shared_ptr<CG::Material> CG::Mesh::getMaterial() const{
    return m_material;
}

void CG::Mesh::addChild(std::shared_ptr<Mesh> newChild){
    m_children.emplace_back(newChild);
}

void CG::Mesh::removeChild(Mesh *objPtr){
    for(unsigned int i = 0; i < m_children.size(); ++i){
        if(m_children[i].get() == objPtr){
            m_children.erase(m_children.begin() + i);
            break;
        }
    }
}

const std::vector<std::shared_ptr<CG::Mesh>>& CG::Mesh::getChildren() const{
    return m_children;
}

void CG::Mesh::setParent(std::shared_ptr<Mesh> obj){
    if(m_parent.lock()){
        m_parent.lock()->removeChild(this);
    }
    m_parent = obj;
}

const std::shared_ptr<CG::Mesh> CG::Mesh::getParent(){
    return m_parent.lock();
}