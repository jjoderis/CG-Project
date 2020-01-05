#include "object3D.h"

CG::Object3D::Object3D() {}

CG::Object3D::Object3D(const Object3D & other) : m_position{ other.m_position } {}

CG::Object3D& CG::Object3D::operator= (const CG::Object3D &other){

    if(&other == this){
        return *this;
    }

    m_position = other.m_position;

    return *this;
}

void CG::Object3D::setPosition(const CG::LinAlg::Vector4<GLfloat> position){
    m_position = position;
}

void CG::Object3D::translate(const CG::LinAlg::Vector4<GLfloat> transVec){
    m_position += transVec;
}

CG::LinAlg::Vector4<GLfloat>& CG::Object3D::getPosition(){
    return m_position;
}

void CG::Object3D::render() const{
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