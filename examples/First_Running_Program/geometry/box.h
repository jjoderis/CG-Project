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
            { 0, 1 },
            { 1, 2 },
            { 2, 3 },
            { 3, 0 },
            { 4, 5 },
            { 5, 6 },
            { 6, 7 },
            { 7, 4 },
            { 0, 4 },
            { 1, 5 },
            { 2, 6 },
            { 3, 7 }
        }
    };

    return boxGeo;
}

#endif