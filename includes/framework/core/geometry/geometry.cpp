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

    updateOpenGL();
}

CG::Geometry::Geometry(const std::vector<CG::Vector3> &vertices, const std::vector<Face3> &faces) 
    : m_vertices{ vertices }, m_faces{ faces }
{
    updateOpenGL();
}

CG::Geometry::Geometry(const CG::Geometry &other) : m_vertices{ other.m_vertices }, m_faces{ other.m_faces } {
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

    glNamedBufferStorage(m_VBO, sizeof(GLfloat) * (3 * m_vertices.size() + 4 * m_vertColors.size()), nullptr, GL_DYNAMIC_STORAGE_BIT);

    int i = 0;
    for(CG::Vector3 &vertex : m_vertices){
        glNamedBufferSubData(m_VBO, 3 * i * sizeof(GLfloat), 3 * sizeof(GLfloat), vertex.data());
        ++i;
    }

    i = 0;
    if(m_vertColors.size()){
        for(CG::RGBA_Color &color : m_vertColors){
            glNamedBufferSubData(m_VBO, 4 * i * sizeof(GLfloat) + 3 * sizeof(GLfloat) * m_vertices.size(), 4 * sizeof(GLfloat), color.data());
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

    glEnableVertexAttribArray(0);

    if(m_vertColors.size()){
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3 * sizeof(GLfloat) * m_vertices.size()));
        glEnableVertexAttribArray(1);
    }
}

void CG::Geometry::setVertices(const std::vector<CG::Vector3> &vertices){
    if(m_vertices.size() != m_vertColors.size()){
        m_vertColors.clear();
    }

    m_vertices = vertices;
    updateOpenGL();
}

void CG::Geometry::setFaces(const std::vector<CG::Face3> &faces){
    m_faces = faces;
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

void CG::Geometry::draw() const {
    glBindVertexArray(m_VAO);
    if(m_faces.size()){
        glDrawElements(GL_TRIANGLES, 3 * m_faces.size(), GL_UNSIGNED_INT, NULL);
    }else{
        glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    }
}

bool CG::operator== (const Geometry &g1, const Geometry &g2){
    return ((g1.m_vertices == g2.m_vertices) && (g1.m_faces == g2.m_faces));
}