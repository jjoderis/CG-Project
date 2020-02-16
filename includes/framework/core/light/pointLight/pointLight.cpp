#include "pointLight.h"

CG::PointLight::PointLight(const Vector3 &position) : Light(){
    m_position = position;
}

CG::PointLight::PointLight(const Vector3 &position, float cAttenuation, float lAttenuation, float qAttenuation) : PointLight(position){
    m_constantAttenuation = cAttenuation;
    m_linearAttenuation = lAttenuation;
    m_quadraticAttenuation = qAttenuation;
}