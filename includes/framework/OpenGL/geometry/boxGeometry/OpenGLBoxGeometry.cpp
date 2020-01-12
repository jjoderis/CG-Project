#include "OpenGLBoxGeometry.h"

CG::OpenGLBoxGeometry::OpenGLBoxGeometry(float width, float height, float depth) : BoxGeometry(width, height, depth), OpenGLGeometry() {
    updateOpenGL();
}