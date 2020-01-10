#include "OpenGLGeometry.h"

CG::OpenGLGeometry::OpenGLGeometry() : Geometry() {}

CG::OpenGLGeometry::OpenGLGeometry(const std::initializer_list<float> &vertexData, const std::initializer_list<int> &faceData)
    : Geometry(vertexData, faceData)
{
    updateOpenGL();
}

CG::OpenGLGeometry::OpenGLGeometry(const std::initializer_list<CG::Vector3> &vertices, const std::initializer_list<CG::Face3> &faces)
    : Geometry{vertices, faces}
{
    updateOpenGL();
}

CG::OpenGLGeometry::OpenGLGeometry(const std::vector<CG::Vector3> &vertices, const std::vector<Face3> &faces)
    : Geometry{vertices, faces}
{
    updateOpenGL();
}

CG::OpenGLGeometry::OpenGLGeometry(const CG::OpenGLGeometry &other)
    : Geometry{ other }
{
    updateOpenGL();
}

CG::OpenGLGeometry& CG::OpenGLGeometry::operator= (const CG::OpenGLGeometry &other){
    //handle self assignment
    if(this == &other){
        return *this;
    }

    Geometry::operator=(other);
    updateOpenGL();

    return *this;
}

CG::OpenGLGeometry::~OpenGLGeometry() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void CG::OpenGLGeometry::setVertices(const std::vector<CG::Vector3> &vertices){
    Geometry::setVertices(vertices);

    updateOpenGL();
}

void CG::OpenGLGeometry::setFaces(const std::vector<CG::Face3> &faces){
    Geometry::setFaces(faces);

    updateOpenGL();
}

void CG::OpenGLGeometry::clearFaces(){
    Geometry::clearFaces();
    updateOpenGL();
}

void CG::OpenGLGeometry::setVertexColors(const std::vector<CG::RGBA_Color> &colors){
    Geometry::setVertexColors(colors);
    updateOpenGL();
}

void CG::OpenGLGeometry::clearColors(){
    Geometry::clearColors();
    updateOpenGL();
}

void CG::OpenGLGeometry::updateOpenGL() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);

    long unsigned int numVertices{ m_vertices.size() };
    //create and populate vertex buffer
    glCreateBuffers(1, &m_VBO);
    //allocate buffer space for vertices normals and optionally colors
    glNamedBufferStorage(m_VBO, sizeof(float) * (2 * 3 * numVertices + 4 * m_vertColors.size()), nullptr, GL_DYNAMIC_STORAGE_BIT);

    for(unsigned int i = 0; i < numVertices; ++i){
        glNamedBufferSubData(m_VBO, 3 * i * sizeof(float), 3 * sizeof(float), m_vertices[i].data());
        glNamedBufferSubData(m_VBO, 3 * i * sizeof(float) + 3 * sizeof(float) * numVertices, 3 * sizeof(float), m_vertNormals[i].data());
    }

    int i = 0;
    if(m_vertColors.size()){
        for(CG::RGBA_Color &color : m_vertColors){
            glNamedBufferSubData(m_VBO, 4 * i * sizeof(float) + 2 * 3 * sizeof(float) * numVertices, 4 * sizeof(float), color.data());
            ++i;
        }
    }

    std::vector<float> indices(2 * 3 * numVertices);

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    //create and populate index buffer if needed
    if(m_faces.size()){
        long unsigned int numFaces = m_faces.size();
        std::vector<unsigned int> indices(3 * numFaces);

        for(unsigned int i = 0; i < numFaces; ++i){
            indices[3*i] = m_faces[i].a;
            indices[3*i+1] = m_faces[i].b;
            indices[3*i+2] = m_faces[i].c;
        }

        glCreateBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int) * numFaces, indices.data(), GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3 * sizeof(GLfloat) * numVertices));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    if(m_vertColors.size()){
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * 3 * sizeof(GLfloat) * numVertices));
        glEnableVertexAttribArray(2);
    }
}

int CG::OpenGLGeometry::getVAO() const{
    return m_VAO;
}