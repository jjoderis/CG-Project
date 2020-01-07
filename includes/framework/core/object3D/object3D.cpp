#include "object3D.h"

CG::Object3D::Object3D() : m_shear{ createIdentityMatrix() }, m_worldMatrix{ createIdentityMatrix() } {}

CG::Object3D::Object3D(const Object3D & other) : Object3D() {
    *this = other;
}

CG::Object3D& CG::Object3D::operator= (const CG::Object3D &other){

    if(&other == this){
        return *this;
    }

    m_position = other.m_position;
    m_scale = other.m_scale;
    m_rotation = other.m_rotation;
    m_shear = other.m_shear;
    m_worldMatrix = other.m_worldMatrix;
    m_parent = other.m_parent;
    m_children = other.m_children;

    updateMatrixWorld();

    return *this;
}

void CG::Object3D::updateMatrixWorld(){   
    CG::Matrix4 transMat{createTranslationMatrix(m_position)};
    

    CG::Matrix4 rotMat{ createRotationMatrix(m_rotation) };

    CG::Matrix4 scaleMat{createScalingMatrix(m_scale)};
    
    m_worldMatrix = dot(transMat, rotMat);
    m_worldMatrix = dot(m_worldMatrix, scaleMat);

    CG::Matrix4 transmatInv{createTranslationMatrix(-m_position)};
    CG::Matrix4 rotMatInv{ rotMat.transpose() };
    CG::Matrix4 scaleMatInv{ createScalingMatrix(Vector3{1.0f/m_scale.at(0), 1.0f/m_scale.at(1), 1.0f/m_scale.at(2)}) };

    m_worldMatrixInverse = dot(scaleMatInv, rotMatInv);
    m_worldMatrixInverse = dot(m_worldMatrixInverse, rotMatInv);

    if(m_parent.lock()){
        m_worldMatrix = dot(m_parent.lock()->m_worldMatrix, m_worldMatrix);
        m_worldMatrixInverse = dot(m_worldMatrix, m_parent.lock()->m_worldMatrix);
    }

    for(unsigned int i = 0; i < m_children.size(); ++i){
        m_children[i]->updateMatrixWorld();
    }
}

void CG::Object3D::setPosition(const CG::Vector3 &position){
    m_position = position;
}
void CG::Object3D::setPosition(GLfloat x, GLfloat y, GLfloat z){
    m_position.at(0) = x;
    m_position.at(1) = y;
    m_position.at(2) = z;
}

void CG::Object3D::translate(const CG::Vector3 &transVec){
    m_position += transVec;
}
void CG::Object3D::translate(GLfloat x, GLfloat y, GLfloat z){
    m_position.at(0) += x;
    m_position.at(1) += y;
    m_position.at(2) += z;
}

void CG::Object3D::setScale(const CG::Vector3 &scales){
    m_scale = scales;
}
void CG::Object3D::setScale(GLfloat xFac, GLfloat yFac, GLfloat zFac){
    m_scale.at(0) = xFac;
    m_scale.at(1) = yFac;
    m_scale.at(2) = zFac;
}
void CG::Object3D::scale(const CG::Vector3 &scales){
    m_scale *= scales;
}
void CG::Object3D::scale(GLfloat xFac, GLfloat yFac, GLfloat zFac){
    m_scale.at(0) *= xFac;
    m_scale.at(1) *= yFac;
    m_scale.at(2) *= zFac;
}
void CG::Object3D::scale(GLfloat scale){
    m_scale *= scale;
}


void CG::Object3D::setRotation(const CG::Quaternion &rotation){
    m_rotation = rotation;
    m_rotation.normalize();
}

void CG::Object3D::setRotation(const CG::Vector3 &axis, GLfloat amount){
    m_rotation = Quaternion{sin(amount/2)*normalize(axis), cos(amount/2)};
}

void CG::Object3D::setRotation(GLfloat axisX, GLfloat axisY, GLfloat axisZ, GLfloat amount){
    setRotation(Vector3{ axisX, axisY, axisZ }, amount);
}

void CG::Object3D::rotate(const CG::Vector3 &axis, GLfloat amount){
    m_rotation *= Quaternion{sin(amount/2)*normalize(axis), cos(amount/2)};
}

void CG::Object3D::rotate(GLfloat axisX, GLfloat axisY, GLfloat axisZ, GLfloat amount){
    rotate(Vector3{ axisX, axisY, axisZ }, amount);
}

void CG::Object3D::rotateX(GLfloat amount){
    rotate(Vector3{ 1.0f, 0.0f, 0.0f }, amount);
}
void CG::Object3D::rotateY(GLfloat amount){
    rotate(Vector3{ 0.0f, 1.0f, 0.0f }, amount);
}
void CG::Object3D::rotateZ(GLfloat amount){
    rotate(Vector3{ 0.0f, 0.0f, 1.0f }, amount);
}

void CG::Object3D::resetRotation(){
    m_rotation = CG::Quaternion{ 0.0, 0.0, 0.0, 1.0 };
}

void CG::Object3D::shear(int sheared, int shearing, float amount){
    Matrix4 shearMat = createShearingMatrix(sheared, shearing, amount);
    m_shear = dot(shearMat, m_shear);
}
void CG::Object3D::resetShearing(){
    m_shear = createIdentityMatrix();
}

CG::Vector3& CG::Object3D::getPosition(){
    return m_position;
}

CG::Vector3& CG::Object3D::getScale(){
    return m_scale;
}

CG::Quaternion& CG::Object3D::getRotation(){
    return m_rotation;
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