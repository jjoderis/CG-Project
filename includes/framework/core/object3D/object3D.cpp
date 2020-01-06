#include "object3D.h"

CG::Object3D::Object3D() : m_worldMatrix{ createIdentityMatrix() } {}

CG::Object3D::Object3D(const Object3D & other) : Object3D() {
    m_position = other.m_position;
}

CG::Object3D& CG::Object3D::operator= (const CG::Object3D &other){

    if(&other == this){
        return *this;
    }

    m_position = other.m_position;
    m_scale = other.m_scale;
    m_worldMatrix = other.m_worldMatrix;
    m_parent = other.m_parent;
    m_children = other.m_children;

    return *this;
}

void CG::Object3D::updateMatrixWorld(){   
    CG::Matrix4 transMat = createTranslationMatrix(m_position);
    CG::Matrix4 rotMat = createRotationMatrix();
    CG::Matrix4 scaleMat = createScalingMatrix(m_scale);
    
    m_worldMatrix = dot(transMat, rotMat);
    m_worldMatrix = dot(m_worldMatrix, scaleMat);

    if(m_parent.lock()){
        m_worldMatrix = dot(m_parent.lock()->m_worldMatrix, m_worldMatrix);
    }

    for(unsigned int i = 0; i < m_children.size(); ++i){
        m_children[i]->updateMatrixWorld();
    }
}

void CG::Object3D::setPosition(const CG::Vector3 &position){
    m_position = position;
}

void CG::Object3D::translate(const CG::Vector3 &transVec){
    m_position += transVec;
}

void CG::Object3D::setScale(const CG::Vector3 &scales){
    m_scale = scales;
}
void CG::Object3D::scale(const CG::Vector3 &scales){
    m_scale *= scales;
}
void CG::Object3D::scale(GLfloat scale){
    m_scale *= scale;
}

CG::Vector3& CG::Object3D::getPosition(){
    return m_position;
}

CG::Vector3& CG::Object3D::getScale(){
    return m_scale;
}

void CG::Object3D::render(){
    for(const std::shared_ptr<CG::Object3D> &child : m_children){
        child->render();
    }
}

void CG::Object3D::addChild(std::shared_ptr<CG::Object3D> newChild){
    m_children.emplace_back(newChild);
}

void CG::Object3D::removeChild(CG::Object3D *objPtr){
    for(unsigned int i = 0; i < m_children.size(); ++i){
        if(m_children[i].get() == objPtr){
            m_children.erase(m_children.begin() + i);
            break;
        }
    }
}

const std::vector<std::shared_ptr<CG::Object3D>>& CG::Object3D::getChildren(){
    return m_children;
}

void CG::Object3D::setParent(std::shared_ptr<CG::Object3D> obj){
    if(m_parent.lock()){
        m_parent.lock()->removeChild(this);
    }
    m_parent = obj;
}

const std::shared_ptr<CG::Object3D> CG::Object3D::getParent(){
    return m_parent.lock();
}