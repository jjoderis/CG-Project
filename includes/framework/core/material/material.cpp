#include "material.h"

CG::Material::Material(){}

CG::Material::Material(CG::RGBA_Color color) : Material() {
    m_color = color;
}

CG::Material::Material(CG::RGB_Color color) : Material(CG::RGBA_Color(color, 1.0)) {}

CG::Material::Material(const CG::Material &other){
    *this = other;
}

CG::Material& CG::Material::operator= (const CG::Material &other){
    m_color = other.m_color;

    return *this;
}

CG::Material::~Material(){}

void CG::Material::setColor(CG::RGB_Color color){
    m_color = CG::RGBA_Color{color, 1.0};
}

void CG::Material::setColor(float r, float g, float b){
    m_color = CG::RGBA_Color{ r, g, b, 1.0 };
}

void CG::Material::setColor(CG::RGBA_Color color){
    m_color = color;
}

void CG::Material::setColor(float r, float g, float b, float a){
    m_color = CG::RGBA_Color{ r, g, b, a };
}

CG::RGBA_Color& CG::Material::getColor(){
    return m_color;
}