#ifndef CG_EXAMPLES_SETUP_MATERIAL_PHONG_H
#define CG_EXAMPLES_SETUP_MATERIAL_PHONG_H

#include <OpenGL/material/OpenGLMaterial.h>
#include <fileHandling/fileHandler.h>
#include <stb_image.h>

CG::OpenGLMaterial setUpPhongMaterial(){
    CG::OpenGLMaterial phongMat = CG::OpenGLMaterial{
        readTextFile("../media/shaders/texturePhong/phong.vert"),
        readTextFile("../media/shaders/texturePhong/phong.frag")
    };

    phongMat.setShininess(120.0);

    phongMat.addUniform("modelViewMatrix");
    phongMat.addUniform("projectionMatrix");
    phongMat.addUniform("normalMatrix");
    phongMat.addUniform("viewMatrix");
    phongMat.addUniform("baseColor");
    phongMat.addUniform("shininess");
    phongMat.addUniform("modelMatrix");

    unsigned int texObj{ 0 };
    glCreateTextures(GL_TEXTURE_2D, 1, &texObj);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(0);

    unsigned char* data = stbi_load("../media/textures/earth.jpg", &width, &height, &nrChannels, 0);

    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
    phongMat.addTexture(texObj);

    return phongMat;
}

#endif