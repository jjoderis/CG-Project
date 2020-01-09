#include "quaternion.h"

CG::Quaternion::Quaternion() {}

CG::Quaternion::Quaternion(const Vector3 &imaginary, GLfloat real) : m_imaginary{ imaginary }, m_real{ real } {}

CG::Quaternion::Quaternion(GLfloat qx, GLfloat qy, GLfloat qz, GLfloat qw)
    : m_imaginary{ qx, qy, qz }, m_real{qw} {}

CG::Quaternion::Quaternion(const Quaternion &other) : m_imaginary{ other.m_imaginary }, m_real{ other.m_real } {}

CG::Quaternion& CG::Quaternion::operator= (const Quaternion &other){

    if(&other == this){
        return *this;
    }

    this->m_imaginary = other.m_imaginary;
    this->m_real = other.m_real;

    return *this;
}

void CG::Quaternion::setReal(GLfloat val){
    m_real = val;
}
void CG::Quaternion::setImaginary(Vector3 &vec){
    m_imaginary = vec;
}
void CG::Quaternion::setImaginary(GLfloat qx, GLfloat qy, GLfloat qz){
    m_imaginary = Vector3{ qx, qy, qz };
}

GLfloat CG::Quaternion::getReal() const{
    return m_real;
}
CG::Vector3& CG::Quaternion::getImaginary(){
    return m_imaginary;
}

CG::Quaternion& CG::Quaternion::operator*= (const Quaternion &other){
    GLfloat newReal = m_real * other.m_real - m_imaginary.dot(other.m_imaginary);
    Vector3 newImaginary = cross(m_imaginary, other.m_imaginary) + other.m_real * m_imaginary + m_real * other.m_imaginary;

    m_real = newReal;
    m_imaginary = newImaginary;

    return *this;
}

CG::Quaternion& CG::Quaternion::operator*= (GLfloat s){
    m_imaginary *= s;
    m_real *= s;

    return *this;
}

CG::Quaternion& CG::Quaternion::operator+= (const Quaternion &other){
    m_imaginary += other.m_imaginary;
    m_real += other.m_real;

    return *this;
}

CG::Quaternion CG::Quaternion::conjugate() const{
    return Quaternion{ -m_imaginary, m_real };
}

GLfloat CG::Quaternion::norm() const{
    return sqrt(pow(m_imaginary.at(0) , 2) + pow(m_imaginary.at(1) , 2) + pow(m_imaginary.at(2) , 2) + pow(m_real, 2));
}

void CG::Quaternion::normalize(){
    m_imaginary.normalize();
    m_imaginary *= sin(m_real/2);
    m_real = cos(m_real/2);
}

CG::Quaternion CG::Quaternion::inverse() const{
    return (1 / pow(norm(), 2)) * conjugate();
}

CG::Quaternion& CG::Quaternion::invert(){
    *this = inverse();

    return *this;
}

CG::Quaternion CG::operator* (const Quaternion &q1, const Quaternion &q2){
    return Quaternion{ 
        cross(q1.m_imaginary, q2.m_imaginary) + q2.m_real * q1.m_imaginary + q1.m_real * q2.m_imaginary
        , q1.m_real*q2.m_real - (float)q1.m_imaginary.dot(q2.m_imaginary)
    };
}

CG::Quaternion CG::operator* (const Quaternion q, GLfloat s){
    return Quaternion{ s *  q.m_imaginary, s * q.m_real };
}
CG::Quaternion CG::operator* (GLfloat s, const Quaternion q){
    return Quaternion{ s *  q.m_imaginary, s * q.m_real };
}

CG::Quaternion CG::operator+ (const Quaternion &q1, const Quaternion &q2){
    return Quaternion{ q1.m_imaginary + q2.m_imaginary, q1.m_real + q2.m_real };
}

std::ostream& CG::operator<< (std::ostream &out, const Quaternion &q){
    
    out << q.m_imaginary.at(0) << "i + " << q.m_imaginary.at(1) << "j + " << q.m_imaginary.at(2) << "k + " << q.m_real << '\n';

    return out;
}

CG::Quaternion CG::slerp (const Quaternion &q1, const Quaternion &q2, GLfloat fraction){
    GLfloat phi = q1.m_imaginary.at(0) * q2.m_imaginary.at(0) + q1.m_imaginary.at(1) * q2.m_imaginary.at(1) + q1.m_imaginary.at(1) * q2.m_imaginary.at(1)
                + q1.m_imaginary.at(2) * q2.m_imaginary.at(2) + q1.m_real + q2.m_real;

    return (sin(phi * (1 - fraction)) / sin(phi)) * q1 + (sin(phi * fraction) / sin(phi)) * q2;
}

CG::Matrix4 CG::createRotationMatrix(Quaternion &q){
    Vector3 i = q.getImaginary();
    GLfloat r = q.getReal();
    return Matrix4{
        { 1.0f- 2.0f*((float)pow(i.at(1), 2)+(float)pow(i.at(2), 2)), 2.0f*(i.at(0)*i.at(1)-r*i.at(2)), 2.0f*(i.at(0)*i.at(2)+r*i.at(1)), 0.0f},
        { 2.0f*(i.at(0)*i.at(1)+r*i.at(2)), 1.0f- 2.0f*((float)pow(i.at(0), 2)+(float)pow(i.at(2), 2)), 2.0f*(i.at(1)*i.at(2)-r*i.at(0)), 0.0f},
        { 2.0f*(i.at(0)*i.at(2)-r*i.at(1)), 2.0f*(i.at(1)*i.at(2)+r*i.at(0)), 1.0f- 2.0f*((float)pow(i.at(0), 2)+(float)pow(i.at(1), 2)), 0.0f},
        { 0.0f, 0.0f, 0.0f, 1.0f}
    };
}