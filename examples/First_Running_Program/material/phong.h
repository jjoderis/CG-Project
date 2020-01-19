#ifndef CG_EXAMPLES_SETUP_MATERIAL_PHONG_H
#define CG_EXAMPLES_SETUP_MATERIAL_PHONG_H

#include <OpenGL/material/OpenGLMaterial.h>
#include <fileHandling/fileHandler.h>

CG::OpenGLMaterial setUpPhongMaterial(){
    CG::OpenGLMaterial phongMat = CG::OpenGLMaterial{
        readTextFile("../media/shaders/phongShader/phong.vert"),
        readTextFile("../media/shaders/phongShader/phong.frag")
    };

    phongMat.setShininess(120.0);

    phongMat.addUniform("modelViewMatrix");
    phongMat.addUniform("projectionMatrix");
    phongMat.addUniform("normalMatrix");
    phongMat.addUniform("viewMatrix");
    phongMat.addUniform("baseColor");
    phongMat.addUniform("shininess");
    phongMat.addUniform("modelMatrix");

    return phongMat;
}

#endif