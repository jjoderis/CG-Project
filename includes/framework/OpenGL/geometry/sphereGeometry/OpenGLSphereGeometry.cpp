#include "OpenGLSphereGeometry.h"

CG::OpenGLSphereGeometry::OpenGLSphereGeometry(float radius, unsigned int widthSegs, unsigned int heightSegs)
    : SphereGeometry(radius, widthSegs, heightSegs), OpenGLGeometry()
{
    updateOpenGL();
}