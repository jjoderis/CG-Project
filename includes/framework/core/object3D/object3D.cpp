#include "object3D.h"

CG::Object3D::Object3D(){}

CG::Object3D::Object3D(const Object3D & other) : Object3D() {
    *this = other;
}

CG::Object3D::~Object3D(){}

CG::Object3D& CG::Object3D::operator= (const CG::Object3D &other){

    if(&other == this){
        return *this;
    }

    m_position = other.m_position;
    m_scale = other.m_scale;
    m_rotation = other.m_rotation;
    m_worldMatrix = other.m_worldMatrix;
    m_worldMatrixInverse = other.m_worldMatrixInverse;
    m_velocity = other.m_velocity;
    m_animationPtr = other.m_animationPtr;
    isAnimated = other.isAnimated;

    updateMatrixWorld();

    return *this;
}

void CG::Object3D::updateMatrixWorld(){   
    CG::Matrix4 transMat{createTranslationMatrix(m_position)};
    

    CG::Matrix4 rotMat{ createRotationMatrix(m_rotation) };

    CG::Matrix4 scaleMat{createScalingMatrix(m_scale)};
    
    m_worldMatrix = transMat * rotMat;
    m_worldMatrix = m_worldMatrix * scaleMat;

    CG::Matrix4 transmatInv{createTranslationMatrix(-m_position)};
    CG::Matrix4 rotMatInv{ rotMat.transpose() };
    CG::Matrix4 scaleMatInv{ createScalingMatrix(Vector3{1.0f/m_scale.at(0), 1.0f/m_scale.at(1), 1.0f/m_scale.at(2)}) };

    m_worldMatrixInverse = scaleMatInv * rotMatInv;
    m_worldMatrixInverse = m_worldMatrixInverse * transmatInv;
    triggerCallbacks("updateMatrixWorld");
}

void CG::Object3D::setPosition(const CG::Vector3 &position){
    m_position = position;
    triggerCallbacks("setPosition");
}
void CG::Object3D::setPosition(float x, float y, float z){
    m_position.at(0) = x;
    m_position.at(1) = y;
    m_position.at(2) = z;
    triggerCallbacks("setPosition");
}

void CG::Object3D::translate(const CG::Vector3 &transVec){
    m_position += transVec;
    triggerCallbacks("translate");
}
void CG::Object3D::translate(float x, float y, float z){
    m_position.at(0) += x;
    m_position.at(1) += y;
    m_position.at(2) += z;
    triggerCallbacks("translate");
}

void CG::Object3D::setScale(const CG::Vector3 &scales){
    m_scale = scales;
    triggerCallbacks("setScale");
}
void CG::Object3D::setScale(float xFac, float yFac, float zFac){
    m_scale.at(0) = xFac;
    m_scale.at(1) = yFac;
    m_scale.at(2) = zFac;
    triggerCallbacks("setScale");
}
void CG::Object3D::scale(const CG::Vector3 &scales){
    m_scale *= scales;
    triggerCallbacks("scale");
}
void CG::Object3D::scale(float xFac, float yFac, float zFac){
    m_scale.at(0) *= xFac;
    m_scale.at(1) *= yFac;
    m_scale.at(2) *= zFac;
    triggerCallbacks("scale");
}
void CG::Object3D::scale(float scale){
    m_scale *= scale;
    triggerCallbacks("scale");
}


void CG::Object3D::setRotation(const CG::Quaternion &rotation){
    m_rotation = rotation;
    m_rotation.normalize();
    triggerCallbacks("setRotation");
}

void CG::Object3D::setRotation(const CG::Vector3 &axis, float amount){
    m_rotation = Quaternion{sin(amount/2)*normalize(axis), cos(amount/2)};
    triggerCallbacks("setRotation");
}

void CG::Object3D::setRotation(float axisX, float axisY, float axisZ, float amount){
    setRotation(Vector3{ axisX, axisY, axisZ }, amount);
}

void CG::Object3D::rotate(const CG::Vector3 &axis, float amount){
    m_rotation *= Quaternion{sin(amount/2)*normalize(axis), cos(amount/2)};
    triggerCallbacks("rotate");
}

void CG::Object3D::rotate(float axisX, float axisY, float axisZ, float amount){
    rotate(Vector3{ axisX, axisY, axisZ }, amount);
}

void CG::Object3D::rotateX(float amount){
    rotate(Vector3{ 1.0f, 0.0f, 0.0f }, amount);
}
void CG::Object3D::rotateY(float amount){
    rotate(Vector3{ 0.0f, 1.0f, 0.0f }, amount);
}
void CG::Object3D::rotateZ(float amount){
    rotate(Vector3{ 0.0f, 0.0f, 1.0f }, amount);
}

void CG::Object3D::resetRotation(){
    m_rotation = CG::Quaternion{ 0.0, 0.0, 0.0, 1.0 };
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

const CG::Matrix4& CG::Object3D::getMatrixWorld() const{
    return m_worldMatrix;
}
const CG::Matrix4& CG::Object3D::getMatrixWorldInverse() const{
    return m_worldMatrixInverse;
}

void CG::Object3D::setVelocity(const Vector3 &velocity){
    m_velocity = velocity;
}
const CG::Vector3& CG::Object3D::getVelocity(){
    return m_velocity;
}

void CG::Object3D::animate(){
    m_animationPtr(*this);
}

void CG::Object3D::setAnimation(std::function<void(CG::Object3D&)> const &animationFunction){
    m_animationPtr = animationFunction;
    isAnimated = true;
}
void CG::Object3D::deleteAnimation(){
    m_animationPtr = nullptr;
    isAnimated = false;
}

void CG::Object3D::registerForCallback(const Object3D *registeringObject, std::function<void(const char* event)> const &callback){
    m_eventHandling.insert({registeringObject, callback});
}
void CG::Object3D::unregisterFromCallback(const Object3D *unregisteringObject){
    m_eventHandling.erase(unregisteringObject);
}

void CG::Object3D::triggerCallbacks(const char* event) const{
    auto it = m_eventHandling.begin();

    while (it != m_eventHandling.end()) {
        it->second(event);
        ++it;
    }
}