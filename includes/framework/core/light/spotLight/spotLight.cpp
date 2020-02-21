#include "spotLight.h"

CG::SpotLight::SpotLight(const Vector3 &position) : Light(){
    m_position = position;
    m_isSpot = true;
}

CG::SpotLight::SpotLight(const Vector3 &position, float cAttenuation, float lAttenuation, float qAttenuation) : SpotLight(position){
    m_constantAttenuation = cAttenuation;
    m_linearAttenuation = lAttenuation;
    m_quadraticAttenuation = qAttenuation;
}