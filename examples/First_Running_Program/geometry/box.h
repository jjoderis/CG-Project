#ifndef CG_EXAMPLES_SETUP_BOXGEOMETRY
#define CG_EXAMPLES_SETUP_BOXGEOMETRY

#include <OpenGL/geometry/OpenGLGeometry.h>

CG::OpenGLGeometry setUpBoxGeometry(){
    CG::OpenGLGeometry boxGeo = CG::OpenGLGeometry{
        {
            { -5.0, -5.0, 5.0 },
            {  5.0, -5.0, 5.0 },
            { -5.0, -5.0, 5.0 },
            { -5.0,  5.0, 5.0 },
            {  5.0, -5.0, 5.0 },
            {  5.0,  5.0, 5.0 },
            { -5.0,  5.0, 5.0 },
            {  5.0,  5.0, 5.0 },
            
            { -5.0, -5.0, -5.0 },
            {  5.0, -5.0, -5.0 },
            { -5.0, -5.0, -5.0 },
            { -5.0,  5.0, -5.0 },
            {  5.0, -5.0, -5.0 },
            {  5.0,  5.0, -5.0 },
            { -5.0,  5.0, -5.0 },
            {  5.0,  5.0, -5.0 },

            { -5.0, -5.0, -5.0 },
            { -5.0, -5.0,  5.0 },
            {  5.0, -5.0, -5.0 },
            {  5.0, -5.0,  5.0 },
            { -5.0,  5.0, -5.0 },
            { -5.0,  5.0,  5.0 },
            {  5.0,  5.0, -5.0 },
            {  5.0,  5.0,  5.0 }
        },
        {}
    };

    return boxGeo;
}

#endif