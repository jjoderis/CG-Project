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

CG::LinAlg::Vector4<GLfloat>& CG::Object3D::getPosition(){
    return m_position;
}