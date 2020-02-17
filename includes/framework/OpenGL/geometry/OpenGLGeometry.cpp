#include "OpenGLGeometry.h"

CG::OpenGLGeometry::OpenGLGeometry() : Geometry() {}

CG::OpenGLGeometry::OpenGLGeometry(const std::initializer_list<CG::Vector3> &vertices, const std::initializer_list<CG::Face> &faces)
    : Geometry{vertices, faces}
{
    setUpFaceBasedInformation();
}

CG::OpenGLGeometry::OpenGLGeometry(const std::vector<CG::Vector3> &vertices, const std::vector<Face> &faces)
    : Geometry{vertices, faces}
{
    setUpFaceBasedInformation();
}

CG::OpenGLGeometry::OpenGLGeometry(const CG::OpenGLGeometry &other)
    : Geometry{ other }
{
    *this = other;
    setUpFaceBasedInformation();
}

CG::OpenGLGeometry& CG::OpenGLGeometry::operator= (const CG::OpenGLGeometry &other){
    //handle self assignment
    if(this == &other){
        return *this;
    }

    Geometry::operator=(other);
    m_useNormals = other.m_useNormals;
    m_useColors = other.m_useColors;
    m_useUVs = other.m_useUVs;
    m_drawPrimitive = other.m_drawPrimitive;
    
    setUpFaceBasedInformation();

    return *this;
}

void CG::OpenGLGeometry::setUpFaceBasedInformation(){
    if(m_faces.size()){
        switch(m_faces[0].getNumIndices()){
            case 1:
                m_drawPrimitive = GL_POINTS;
                break;
            case 2:
                m_drawPrimitive = GL_LINES;
                break;
            case 3:
                m_drawPrimitive = GL_TRIANGLES;
                break;
            case 4:
                m_drawPrimitive = GL_QUADS;
                break;
            default:
                calculateFaceNormals();
                calculateVertexNormals();
        }
    } else {
        m_drawPrimitive = GL_POINTS;
    }
    
    updateOpenGL();
}

CG::OpenGLGeometry::~OpenGLGeometry() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void CG::OpenGLGeometry::updateOpenGL() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);

    long unsigned int numVertices{ m_vertices.size() };
    //create and populate vertex buffer
    glCreateBuffers(1, &m_VBO);

    //calculate needed buffer storage space
    long unsigned int vertexSpace{ 3 * sizeof(float) * numVertices };
    long unsigned int normalSpace{ m_useNormals ? 3 * sizeof(float) * numVertices : 0 };
    long unsigned int uvSpace{ m_useUVs ? 2 * sizeof(float) * numVertices : 0 };
    long unsigned int colorSpace{ m_useColors ? 4 * sizeof(float) * numVertices : 0 };
    long unsigned int storageSpace{ vertexSpace + normalSpace + uvSpace + colorSpace };

    //allocate buffer space for vertices normals and optionally colors
    glNamedBufferStorage(m_VBO, storageSpace, nullptr, GL_DYNAMIC_STORAGE_BIT);

    for(unsigned int i = 0; i < numVertices; ++i){
        glNamedBufferSubData(m_VBO, 3 * i * sizeof(float), 3 * sizeof(float), m_vertices[i].data());
        if(m_useNormals){
            glNamedBufferSubData(m_VBO, 3 * i * sizeof(float) + vertexSpace, 3 * sizeof(float), m_vertNormals[i].data());
        }
        if(m_useUVs){
            glNamedBufferSubData(m_VBO, 2 * i * sizeof(float) + vertexSpace + normalSpace, 2 * sizeof(float), m_vertUVs[i].data());
        }
        if(m_useColors){
            glNamedBufferSubData(m_VBO, 4 * i * sizeof(float) + vertexSpace + normalSpace + uvSpace, 4 * sizeof(float), m_vertColors.data());
        }
    }

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    //create and populate index buffer if needed
    if(m_faces.size()){
        long unsigned int numFaces = m_faces.size();
        int indicesPerFace{ m_faces[0].getNumIndices() };
        std::vector<unsigned int> indices(indicesPerFace * numFaces);

        for(unsigned int i = 0; i < numFaces; ++i){
            for(int j = 0; j < indicesPerFace; ++j){
                indices[indicesPerFace * i + j] = m_faces[i].at(j);
            }
        }

        glCreateBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesPerFace * sizeof(unsigned int) * numFaces, indices.data(), GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    int index{ 1 };

    if(m_useNormals){
        glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexSpace));
        glEnableVertexAttribArray(index);
        ++index;
    }

    if(m_useUVs){
        glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexSpace + normalSpace));
        glEnableVertexAttribArray(index);
        ++index;
    }

    if(m_useColors){
        glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexSpace + uvSpace + normalSpace));
        glEnableVertexAttribArray(index);
        ++index;
    }
}

void CG::OpenGLGeometry::activateNormals(){
    m_useNormals = true;
}
void CG::OpenGLGeometry::deactivateNormals(){
    m_useNormals = false;
}
void CG::OpenGLGeometry::activateColors(){
    m_useColors = true;
}
void CG::OpenGLGeometry::deactivateColors(){
    m_useColors = false;
}
void CG::OpenGLGeometry::activateUVs(){
    m_useUVs = true;
}
void CG::OpenGLGeometry::deactivateUVs(){
    m_useUVs = true;
}

int CG::OpenGLGeometry::getVAO() const{
    return m_VAO;
}

void CG::OpenGLGeometry::setVAO(unsigned int VAO){
    m_VAO = VAO;
}

int CG::OpenGLGeometry::getVBO() const{
    return m_VBO;
}

void CG::OpenGLGeometry::setVBO(unsigned int VBO){
    m_VBO = VBO;
}

void CG::OpenGLGeometry::setDrawPrimitive(GLenum primitive){
    m_drawPrimitive = primitive;
}

void CG::OpenGLGeometry::drawGeometry() const{
    glBindVertexArray(m_VAO);
    if(m_faces.size()){
        glDrawElements(m_drawPrimitive, m_faces[0].getNumIndices() * m_faces.size(), GL_UNSIGNED_INT, NULL);
    } else {
        glDrawArrays(m_drawPrimitive, 0, m_vertices.size());
    }
}