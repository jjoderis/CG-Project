#ifndef CG_FRAMEWORK_OPENGL_GEOMETRY_OPENGLBOXGEOMETRY_OPENGLBOXGEOMETRY_H
#define CG_FRAMEWORK_OPENGL_GEOMETRY_OPENGLBOXGEOMETRY_OPENGLBOXGEOMETRY_H

#include <core/geometry/boxGeometry/boxGeometry.h>
#include <OpenGL/geometry/OpenGLGeometry.h>

namespace CG{

    class OpenGLBoxGeometry : public CG::BoxGeometry, public CG::OpenGLGeometry{
    public:
        OpenGLBoxGeometry(float width, float height, float depth);
    };

}

#endif