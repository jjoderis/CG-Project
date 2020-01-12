#include "geometry.h"

CG::Geometry::Geometry() {}

CG::Geometry::Geometry(const std::initializer_list<float> &vertexData, const std::initializer_list<int> &faceData)
{
    assert(vertexData.size() % 3 == 0);
    assert(faceData.size() % 3 == 0);

    m_vertices.resize(vertexData.size() / 3);
    m_faces.resize(faceData.size() / 3);

    int i = 0;
    for (const float &element : vertexData)
    {
        m_vertices[i/3].at(i%3) = element;
        ++i;
    }

    i = 0;
    for (const int &element : faceData)
    {
        switch(i%3){
            case 0:
                m_faces[i/3].a = element;
                break;
            case 1:
                m_faces[i/3].b = element;
                break;
            case 2:
                m_faces[i/3].c = element;
                break;
        }

        ++i;
    }

    calculateVertexNormals();
}

CG::Geometry::Geometry(const std::initializer_list<CG::Vector3> &vertices, const std::initializer_list<CG::Face3> &faces)
{
    m_vertices.resize(vertices.size());
    m_faces.resize(faces.size());

    int i = 0;
    for(const CG::Vector3 &vert : vertices){
        m_vertices[i] = vert;
        ++i;
    }

    i = 0;
    for(const CG::Face3 &face : faces){
        m_faces[i] = face;
        ++i;
    }

    calculateVertexNormals();
}

CG::Geometry::Geometry(const std::vector<CG::Vector3> &vertices, const std::vector<Face3> &faces) 
    : m_vertices{ vertices }, m_faces{ faces }
{
    calculateVertexNormals();
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

    return *this;
}

CG::Geometry::~Geometry() {}

void CG::Geometry::setVertices(const std::vector<CG::Vector3> &vertices){
    if(m_vertices.size() != m_vertColors.size()){
        m_vertColors.clear();
    }

    m_vertices = vertices;

    calculateVertexNormals();
}

void CG::Geometry::setFaces(const std::vector<CG::Face3> &faces){
    m_faces = faces;

    calculateVertexNormals();
}

void CG::Geometry::clearFaces(){
    m_faces.clear();
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

std::vector<CG::Face3>& CG::Geometry::getFaces(){
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
    for(int i = 0; i < numFaces; ++i){
        Vector3 ab{m_vertices[m_faces[i].b] - m_vertices[m_faces[i].a]};
        Vector3 ac{m_vertices[m_faces[i].c] - m_vertices[m_faces[i].a]};
        m_faceNormals[i] = cross(ab, ac).normalize();
    }

}

void CG::Geometry::calculateVertexNormals(){
    calculateFaceNormals();

    std::vector<int> occurences(m_vertices.size());
    m_vertNormals.resize(m_vertices.size());

    long unsigned int numFaces{ m_faces.size() };
    for(unsigned int i = 0; i < numFaces; ++i){
        m_vertNormals[m_faces[i].a] += m_faceNormals[i];
        occurences[m_faces[i].a] += 1;
        m_vertNormals[m_faces[i].b] += m_faceNormals[i];
        occurences[m_faces[i].b] += 1;
        m_vertNormals[m_faces[i].c] += m_faceNormals[i];
        occurences[m_faces[i].c] += 1;
    }

    long unsigned int numVertices{ m_vertices.size() };
    for(unsigned int i = 0; i < numVertices; ++i){
        m_vertNormals[i] /= occurences[i];
        m_vertNormals[i].normalize();
    } 
}