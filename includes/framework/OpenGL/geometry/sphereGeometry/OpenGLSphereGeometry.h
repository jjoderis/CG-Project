#ifndef CG_FRAMEWORK_OPENGL_GEOMETRY_SPHEREGEOMETRY_OPENGLSPHEREGEOMETRY_OPENGLSPHEREGEOMETRY_H
#define CG_FRAMEWORK_OPENGL_GEOMETRY_SPHEREGEOMETRY_OPENGLSPHEREGEOMETRY_OPENGLSPHEREGEOMETRY_H

#include <geometry/sphereGeometry/sphereGeometry.h>
#include <OpenGL/geometry/OpenGLGeometry.h>

namespace CG{

    class OpenGLSphereGeometry : public CG::SphereGeometry, public CG::OpenGLGeometry {
    public:
        OpenGLSphereGeometry(float radius, unsigned int widthSegs, unsigned int heightSegs);
    };

}


#endif