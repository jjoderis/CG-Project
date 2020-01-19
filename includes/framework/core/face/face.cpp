#include "face.h"
#include <iostream>

CG::Face::Face(){
    m_indices.resize(0);
}

CG::Face::Face(unsigned int a, unsigned int b, unsigned int c) : Face(){
    m_indices.emplace_back(a);
    m_indices.emplace_back(b);
    m_indices.emplace_back(c);
}

CG::Face::Face(unsigned int a, unsigned int b, unsigned int c, unsigned int d) : Face(){
    m_indices.emplace_back(a);
    m_indices.emplace_back(b);
    m_indices.emplace_back(c);
    m_indices.emplace_back(d);
}

CG::Face::Face(const Face &other) : Face(){
    *this = other;
}

CG::Face& CG::Face::operator= (const CG::Face &other){
    if(&other == this){
        return *this;
    }

    m_indices.resize(0);

    for(unsigned int i = 0; i < other.m_indices.size(); ++i){
        m_indices.emplace_back(other.m_indices[i]);
    }

    return *this;
}

int CG::Face::getNumIndices() const{
    return m_indices.size();
}

unsigned int& CG::Face::at(int index){
    return m_indices[index];
}

bool CG::operator== (const CG::Face &f1, const CG::Face &f2){
    
    if(f1.m_indices.size() != f2.m_indices.size()){
        return false;
    }

    for(unsigned int i = 0; i < f1.m_indices.size(); ++i){
        if(f1.m_indices[i] != f2.m_indices[i]){
            return false;
        }
    }

    return true;
}

std::ostream& CG::operator<< (std::ostream &out, const CG::Face &face){

    out << "[ 0: " << face.m_indices[0];
    
    for(unsigned int i = 1; i < face.m_indices.size(); ++i){
        out << ", " << i << ": " << face.m_indices[i];
    }

    out << " ]";

    return out;
}