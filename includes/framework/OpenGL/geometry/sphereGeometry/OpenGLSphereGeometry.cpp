#include "OpenGLSphereGeometry.h"

CG::OpenGLSphereGeometry::OpenGLSphereGeometry(float radius, unsigned int widthSegs, unsigned int heightSegs)
    : SphereGeometry(radius, widthSegs, heightSegs), OpenGLGeometry()
{
    calculateFaceNormals();
    calculateVertexNormals();
    activateNormals();
    activateUVs();
    updateOpenGL();
    m_drawPrimitive = GL_TRIANGLES;
}