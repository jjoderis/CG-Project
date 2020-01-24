#include "mesh.h"

template <typename geometryClass, typename materialClass>
CG::Mesh<geometryClass, materialClass>::Mesh() : Object3D() {}

template <typename geometryClass, typename materialClass>
CG::Mesh<geometryClass, materialClass>::Mesh(const geometryClass &geometry, const materialClass &material) 
    : Object3D(),
      m_geometry(std::make_shared<geometryClass>(geometry)),
      m_material(std::make_shared<materialClass>(material))
{}

template <typename geometryClass, typename materialClass>
CG::Mesh<geometryClass, materialClass>::Mesh(const std::shared_ptr<geometryClass> &geometry, const std::shared_ptr<materialClass> &material)
    : Object3D(),
      m_geometry{ geometry },
      m_material{ material }
{}

template <typename geometryClass, typename materialClass>
CG::Mesh<geometryClass, materialClass>::Mesh(const Mesh &other) : Object3D{ other }
{
    *this = other;
}

template <typename geometryClass, typename materialClass>
CG::Mesh<geometryClass, materialClass>& CG::Mesh<geometryClass, materialClass>::operator= (const CG::Mesh<geometryClass, materialClass> &other){

    if(&other == this){
        return *this;
    }

    CG::Object3D::operator=(other);

    m_geometry = other.m_geometry;
    m_material = other.m_material;
    m_position = other.m_position;

    m_parent = other.m_parent;
    m_children = other.m_children;

    return *this;
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::updateMatrixWorld() {
    CG::Object3D::updateMatrixWorld();

    if(m_parent.lock()){
        m_worldMatrix = m_parent.lock()->m_worldMatrix * m_worldMatrix;
        m_worldMatrixInverse = m_worldMatrixInverse * m_parent.lock()->m_worldMatrixInverse;
    }

    for(unsigned int i = 0; i < m_children.size(); ++i){
        m_children[i]->updateMatrixWorld();
    }
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::setName(std::string &name){
    m_name = name;
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::setName(const char* name){
    m_name = name;
}

template <typename geometryClass, typename materialClass>
const std::string& CG::Mesh<geometryClass, materialClass>::getName(){
    return m_name;
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::setGeometry(const geometryClass &geometry){
    m_geometry = std::make_shared<geometryClass>(geometry);
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::setGeometry(const std::shared_ptr<geometryClass> &geometry){
    m_geometry = geometry;
}

template <typename geometryClass, typename materialClass>
std::shared_ptr<geometryClass> CG::Mesh<geometryClass, materialClass>::getGeometry() const{
    return m_geometry;
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::setMaterial(const materialClass &material){
    m_material = std::make_shared<materialClass>(material);
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::setMaterial(const std::shared_ptr<materialClass> &material){
    m_material = material;
}

template <typename geometryClass, typename materialClass>
std::shared_ptr<materialClass> CG::Mesh<geometryClass, materialClass>::getMaterial() const{
    return m_material;
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::addChild(std::shared_ptr<Mesh<geometryClass, materialClass>> newChild){
    m_children.emplace_back(newChild);
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::removeChild(Mesh<geometryClass, materialClass> *objPtr){
    for(unsigned int i = 0; i < m_children.size(); ++i){
        if(m_children[i].get() == objPtr){
            m_children.erase(m_children.begin() + i);
            break;
        }
    }
}

template <typename geometryClass, typename materialClass>
const std::vector<std::shared_ptr<CG::Mesh<geometryClass, materialClass>>>& CG::Mesh<geometryClass, materialClass>::getChildren() const{
    return m_children;
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::setParent(std::shared_ptr<Mesh<geometryClass, materialClass>> obj){
    if(m_parent.lock()){
        m_parent.lock()->removeChild(this);
    }
    m_parent = obj;
}

template <typename geometryClass, typename materialClass>
const std::shared_ptr<CG::Mesh<geometryClass, materialClass>> CG::Mesh<geometryClass, materialClass>::getParent(){
    return m_parent.lock();
}

template <typename geometryClass, typename materialClass>
void CG::Mesh<geometryClass, materialClass>::render(const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){
    (void)viewMatrix;
    (void)viewMatrixInverse;
    (void)projectionMatrix;
}