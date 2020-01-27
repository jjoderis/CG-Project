#ifndef CG_EXAMPLES_TEXTUREEXAMPLE_GEOMETRY_BOX_H
#define CG_EXAMPLES_TEXTUREEXAMPLE_GEOMETRY_BOX_H

#include <OpenGL/geometry/OpenGLGeometry.h>

CG::OpenGLGeometry setUpBox(){
    CG::OpenGLGeometry box {
        {
            { -0.5, -0.5,  0.5 },
            {  0.5, -0.5,  0.5 },
            {  0.5,  0.5,  0.5 },
            { -0.5,  0.5,  0.5 },
            { -0.5, -0.5, -0.5 },
            {  0.5, -0.5, -0.5 },
            {  0.5,  0.5, -0.5 },
            { -0.5,  0.5, -0.5 },
        },
        {
            { 0, 1, 2, 3 },
            { 1, 5, 6, 2 },
            { 5, 4, 7, 6 },
            { 4, 0, 3, 7 },
            { 3, 2, 6, 7 },
            { 4, 5, 1, 0 }
        }
    };

    return box;
}

#endif