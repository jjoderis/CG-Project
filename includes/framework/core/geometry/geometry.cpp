#include "geometry.h"

CG::Geometry::Geometry() {}

CG::Geometry::Geometry(const std::initializer_list<CG::Vector3> &vertices, const std::initializer_list<CG::Face> &faces)
{
    m_vertices.resize(vertices.size());
    m_faces.resize(faces.size());

    int i = 0;
    for(const CG::Vector3 &vert : vertices){
        m_vertices[i] = vert;
        ++i;
    }

    i = 0;
    int faceSize{ 0 };
    (void)faceSize;
    if(faces.size()){
        faceSize = faces.begin()->getNumIndices();
    }

    for(const CG::Face &face : faces){
        assert("Trying to initialize geometry with different types of faces" && face.getNumIndices() == faceSize); 
        m_faces[i] = face;
        ++i;
    }
}

CG::Geometry::Geometry(const std::vector<CG::Vector3> &vertices, const std::vector<Face> &faces) 
    : m_vertices{ vertices }, m_faces{ faces }
{
}

CG::Geometry::Geometry(const CG::Geometry &other)
{
    *this = other;
}

CG::Geometry& CG::Geometry::operator= (const CG::Geometry &other){
    //handle self assignment
    if(this == &other){
        return *this;
    }

    m_vertices = other.m_vertices;
    m_vertNormals = other.m_vertNormals;
    m_faces = other.m_faces;
    m_faceNormals = other.m_faceNormals;
    m_vertColors = other.m_vertColors;

    return *this;
}

CG::Geometry::~Geometry() {}

void CG::Geometry::setVertices(const std::vector<CG::Vector3> &vertices){
    if(m_vertices.size() != m_vertColors.size()){
        m_vertColors.clear();
    }

    m_vertices = vertices;
}

void CG::Geometry::setFaces(const std::vector<CG::Face> &faces){
    m_faces = faces;
}

void CG::Geometry::clearFaces(){
    m_faces.clear();
}

void CG::Geometry::setVertexNormals(const std::vector<CG::Vector3> &vNormals){
    m_vertNormals = vNormals;
}

void CG::Geometry::setFaceNormals(const std::vector<CG::Vector3> &fNormals){
    m_faceNormals = fNormals;
}

void CG::Geometry::setVertexColors(const std::vector<CG::RGBA_Color> &colors){
    if(colors.size() == m_vertices.size()){
        m_vertColors = colors;
    }
}

void CG::Geometry::clearColors(){
    m_vertColors.clear();
}

std::vector<CG::Vector3>& CG::Geometry::getVertices(){
    return m_vertices;
}

std::vector<CG::Vector3>& CG::Geometry::getVertexNormals(){
    return m_vertNormals;
}

int CG::Geometry::getNumVertices() const{
    return m_vertices.size();
}

std::vector<CG::Face>& CG::Geometry::getFaces(){
    return m_faces;
}

std::vector<CG::Vector3>& CG::Geometry::getFaceNormals(){
    return m_faceNormals;
}

int CG::Geometry::getNumFaces() const{
    return m_faces.size();
}

bool CG::operator== (const Geometry &g1, const Geometry &g2){
    return ((g1.m_vertices == g2.m_vertices) && (g1.m_faces == g2.m_faces));
}

void CG::Geometry::calculateFaceNormals(){
    int numFaces = m_faces.size();
    m_faceNormals.resize(numFaces);

    int indexPerFace{ m_faces[0].getNumIndices() };
    for(int i = 0; i < numFaces; ++i){
        Vector3 ab{m_vertices[m_faces[i].at(1)] - m_vertices[m_faces[i].at(0)]};
        Vector3 ac{m_vertices[m_faces[i].at(indexPerFace - 1)] - m_vertices[m_faces[i].at(0)]};
        m_faceNormals[i] = cross(ab, ac).normalize();
    }

}

void CG::Geometry::calculateVertexNormals(){
    std::vector<int> occurences(m_vertices.size());
    m_vertNormals.resize(m_vertices.size());

    long unsigned int numFaces{ m_faces.size() };
    for(unsigned int i = 0; i < numFaces; ++i){
        for(int j = 0; j < m_faces[i].getNumIndices(); ++j){
            m_vertNormals[m_faces[i].at(j)] += m_faceNormals[i];
            occurences[m_faces[i].at(j)] += 1;
        }
    }

    long unsigned int numVertices{ m_vertices.size() };
    for(unsigned int i = 0; i < numVertices; ++i){
        m_vertNormals[i] /= occurences[i];
        m_vertNormals[i].normalize();
    } 
}