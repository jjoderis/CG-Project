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

    // 8 X 8 Checkerboard
    const unsigned short texCheckerboardData[]{
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
    };

    unsigned int texObj{ 0 };
    glCreateTextures(GL_TEXTURE_2D, 1, &texObj);
    glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, 8, 8);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 8, 8, GL_RED, GL_UNSIGNED_BYTE, texCheckerboardData);


    phongMat.addTexture(texObj);

    return phongMat;
}

#endif