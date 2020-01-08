#include "geometry.h"

CG::Geometry::Geometry() {}

CG::Geometry::Geometry(const std::initializer_list<GLfloat> &vertexData, const std::initializer_list<int> &faceData)
{
    assert(vertexData.size() % 3 == 0);
    assert(faceData.size() % 3 == 0);

    m_vertices.resize(vertexData.size() / 3);
    m_faces.resize(faceData.size() / 3);

    int i = 0;
    for (const GLfloat &element : vertexData)
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

    updateOpenGL();
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

    updateOpenGL();
}

CG::Geometry::Geometry(const std::vector<CG::Vector3> &vertices, const std::vector<Face3> &faces) 
    : m_vertices{ vertices }, m_faces{ faces }
{
    calculateVertexNormals();

    updateOpenGL();
}

CG::Geometry::Geometry(const CG::Geometry &other)
    : m_vertices{ other.m_vertices }, m_vertNormals{ other.m_vertNormals }, m_faces{ other.m_faces }, m_faceNormals{ other.m_faceNormals }
{
    updateOpenGL();
}

CG::Geometry& CG::Geometry::operator= (const CG::Geometry &other){
    //handle self assignment
    if(this == &other){
        return *this;
    }

    this->m_vertices = other.m_vertices;
    this->m_faces = other.m_faces;

    updateOpenGL();

    return *this;
}

CG::Geometry::~Geometry() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void CG::Geometry::updateOpenGL() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);

    //create and populate vertex buffer
    glCreateBuffers(1, &m_VBO);
    //allocate buffer space for vertices normals and optionally colors
    glNamedBufferStorage(m_VBO, sizeof(GLfloat) * (2 * 3 * m_vertices.size() + 4 * m_vertColors.size()), nullptr, GL_DYNAMIC_STORAGE_BIT);

    long unsigned int numVertices{ m_vertices.size() };
    for(unsigned int i = 0; i < numVertices; ++i){
        glNamedBufferSubData(m_VBO, 3 * i * sizeof(GLfloat), 3 * sizeof(GLfloat), m_vertices[i].data());
        glNamedBufferSubData(m_VBO, 3 * i * sizeof(GLfloat) + 3 * sizeof(GLfloat) * m_vertices.size(), 3 * sizeof(GLfloat), m_vertNormals[i].data());
    }

    int i = 0;
    if(m_vertColors.size()){
        for(CG::RGBA_Color &color : m_vertColors){
            glNamedBufferSubData(m_VBO, 4 * i * sizeof(GLfloat) + 2 * 3 * sizeof(GLfloat) * m_vertices.size(), 4 * sizeof(GLfloat), color.data());
            ++i;
        }
    }

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    //create and populate index buffer if needed
    if(m_faces.size()){
        unsigned int indices[]{ m_faces[0].a, m_faces[0].b, m_faces[0].c, m_faces[1].a, m_faces[1].b, m_faces[1].c };
        glCreateBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int) * m_faces.size(), indices, GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3 * sizeof(GLfloat) * m_vertices.size()));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    if(m_vertColors.size()){
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * 3 * sizeof(GLfloat) * m_vertices.size()));
        glEnableVertexAttribArray(2);
    }
}

void CG::Geometry::setVertices(const std::vector<CG::Vector3> &vertices){
    if(m_vertices.size() != m_vertColors.size()){
        m_vertColors.clear();
    }

    m_vertices = vertices;

    calculateVertexNormals();

    updateOpenGL();
}

void CG::Geometry::setFaces(const std::vector<CG::Face3> &faces){
    m_faces = faces;

    calculateVertexNormals();

    updateOpenGL();
}

void CG::Geometry::clearFaces(){
    m_faces.clear();
    updateOpenGL();
}

void CG::Geometry::setVertexColors(const std::vector<CG::RGBA_Color> &colors){
    if(colors.size() == m_vertices.size()){
        m_vertColors = colors;
        updateOpenGL();
    }
}

void CG::Geometry::clearColors(){
    m_vertColors.clear();
    updateOpenGL();
}

std::vector<CG::Vector3>& CG::Geometry::getVertices(){
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

int CG::Geometry::getVAO() const{
    return m_VAO;
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
    } 
}