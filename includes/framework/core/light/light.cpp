#include "light.h"

CG::Light::Light() : Camera(1.0, 25.0, degToRad(90.0), 1.0){}

CG::Light::Light(const Light &other) : Camera(other) {
    *this = other;
}

CG::Light& CG::Light::operator= (const Light &other){

    if (this == &other) {
        return *this;
    }

    CG::Object3D::operator=(other);

    m_isEnabled = other.m_isEnabled;
    m_isLocal = other.m_isLocal;

    m_isSpot = other.m_isSpot;
    m_ambient = other.m_ambient;
    m_color = other.m_color;

    m_halfVector = other.m_halfVector;
    m_coneDirection = other.m_coneDirection;
    m_spotCosCutoff = other.m_spotCosCutoff;
    m_spotExponent = other.m_spotExponent;

    m_constantAttenuation = other.m_constantAttenuation;
    m_linearAttenuation = other.m_linearAttenuation;
    m_quadraticAttenuation = other.m_quadraticAttenuation;

    return *this;
}

void CG::Light::enable() {
    m_isEnabled = true;
}

void CG::Light::disable() {
    m_isEnabled = false;
}

void CG::Light::setColor(const CG::RGBA_Color &color) {
    m_color = color;
}

CG::RGBA_Color CG::Light::getColor() const{
    return m_color;
}

void CG::Light::setConstantAttenuation(float attenuation){
    m_constantAttenuation = attenuation;
}
void CG::Light::setLinearAttenuation(float attenuation){
    m_linearAttenuation = attenuation;
}
void CG::Light::setQuadraticAttenuation(float attenuation){
    m_quadraticAttenuation = attenuation;
}

bool CG::Light::isEnabled() const{
    return m_isEnabled;
}
bool& CG::Light::isLocal(){
    return m_isLocal;
}
bool& CG::Light::isSpot(){
    return m_isSpot;
}
CG::Vector4& CG::Light::ambient(){
    return m_ambient;
}
CG::RGBA_Color& CG::Light::color(){
    return m_color;
}
CG::Vector4& CG::Light::halfVector(){
    return m_halfVector;
}
CG::Vector4& CG::Light::coneDirection(){
    return m_coneDirection;
}
float& CG::Light::spotCosCutoff(){
    return m_spotCosCutoff;
}
float& CG::Light::spotExponent(){
    return m_spotExponent;
}
float& CG::Light::constantAttenuation(){
    return m_constantAttenuation;
}
float& CG::Light::linearAttenuation(){
    return m_linearAttenuation;
}
float& CG::Light::quadraticAttenuation(){
    return m_quadraticAttenuation;
}

