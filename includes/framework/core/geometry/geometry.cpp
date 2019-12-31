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

    updateOpenGL();
}

CG::Geometry::Geometry(const std::initializer_list<CG::LinAlg::Vector3<float>> &vertices, const std::initializer_list<CG::Face3> &faces)
    : m_vertices{ vertices }, m_faces{ faces }
{
    updateOpenGL();
}

CG::Geometry::Geometry(const std::vector<CG::LinAlg::Vector3<float>> &vertices, const std::vector<Face3> &faces) 
    : m_vertices{ vertices }, m_faces{ faces }
{
    updateOpenGL();
}

CG::Geometry::Geometry(const CG::Geometry &other) : m_vertices{ other.m_vertices }, m_faces{ other.m_faces } {}

void CG::Geometry::updateOpenGL() {
    glCreateBuffers(1, &Buffer);
    std::vector<float> tmp;
    tmp.resize(3*m_vertices.size());
    for(unsigned int i = 0; i < 3*m_vertices.size(); ++i){
        tmp[i] = m_vertices[i/3][i%3];
    }
    glNamedBufferStorage(Buffer, sizeof(float) * tmp.size(), tmp.data(), 0);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, Buffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);
}

CG::Geometry::~Geometry() {
    glDeleteVertexArrays(1, &VAO);
}

void CG::Geometry::setVertices(const std::vector<CG::LinAlg::Vector3<float>> &vertices){
    m_vertices = vertices;
}

void CG::Geometry::setFaces(const std::vector<CG::Face3> &faces){
    m_faces = faces;
}

std::vector<CG::LinAlg::Vector3<float>>& CG::Geometry::getVertices(){
    return m_vertices;
}

int CG::Geometry::getNumVertices() const{
    return m_vertices.size();
}

std::vector<CG::Face3>& CG::Geometry::getFaces(){
    return m_faces;
}

int CG::Geometry::getNumFaces() const{
    return m_faces.size();
}

void CG::Geometry::bind() const {
    glBindVertexArray(VAO);
}

bool CG::operator== (const Geometry &g1, const Geometry &g2){
    return ((g1.m_vertices == g2.m_vertices) && (g1.m_faces == g2.m_faces));
}