#ifndef CG_EXAMPLES_SETUP_MATERIAL_PHONG_H
#define CG_EXAMPLES_SETUP_MATERIAL_PHONG_H

#include <OpenGL/material/OpenGLMaterial.h>
#include <fileHandling/fileHandler.h>

CG::OpenGLMaterial setUpPhongMaterial(){
    CG::OpenGLMaterial phongMat = CG::OpenGLMaterial{
        CG::ShaderInfo{ GL_VERTEX_SHADER, "../media/shaders/lighting/lighting.vert", true, 0 },
        CG::ShaderInfo{ GL_FRAGMENT_SHADER, "../media/shaders/lighting/lighting.frag", true, 0 }
    };

    phongMat.setShininess(120.0);

    return phongMat;
}

#endif