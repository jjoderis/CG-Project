#ifndef CG_EXAMPLES_SETUP_BOXGEOMETRY
#define CG_EXAMPLES_SETUP_BOXGEOMETRY

#include <OpenGL/geometry/OpenGLGeometry.h>

CG::OpenGLGeometry setUpBoxGeometry(){
    CG::OpenGLGeometry boxGeo = CG::OpenGLGeometry{
        {
            { -5.0, -5.0,  5.0 },
            {  5.0, -5.0,  5.0 },
            {  5.0,  5.0,  5.0 },
            { -5.0,  5.0,  5.0 },
            { -5.0, -5.0, -5.0 },
            {  5.0, -5.0, -5.0 },
            {  5.0,  5.0, -5.0 },
            { -5.0,  5.0, -5.0 }
        },
        {
            { 0, 1, 2, 3},
            { 1, 5, 6, 2},
            { 5, 4, 7, 6},
            { 4, 0, 3, 7},
            { 3, 2, 6, 7},
            { 4, 5, 1, 0}
        }
    };

    return boxGeo;
}

#endif