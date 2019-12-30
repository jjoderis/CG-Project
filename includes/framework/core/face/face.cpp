#include "face.h"
#include <iostream>

CG::Face3::Face3(unsigned int a, unsigned int b, unsigned int c) : a(a), b(b), c(c) {}

CG::Face3::Face3(const Face3 &other) : a(other.a), b(other.b), c(other.c) {}

CG::Face3& CG::Face3::operator= (const CG::Face3 &other){
    a = other.a;
    b = other.b;
    c = other.c;

    return *this;
}

bool CG::operator== (const CG::Face3 &f1, const CG::Face3 &f2){
    return ((f1.a == f2.a) && (f1.b == f2.b) && (f1.c == f2.c));
}

std::ostream& CG::operator<< (std::ostream &out, const CG::Face3 &face){
    out << "[ a: " << face.a << ", b: " << face.b << ", c: " << face.c << " ]";

    return out;
}