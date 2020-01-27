#ifndef CG_EXAMPLES_SETUP_MATERIAL_PHONG_H
#define CG_EXAMPLES_SETUP_MATERIAL_PHONG_H

#include <OpenGL/material/OpenGLMaterial.h>
#include <fileHandling/fileHandler.h>

CG::OpenGLMaterial setUpPhongMaterial(){
    CG::OpenGLMaterial phongMat = CG::OpenGLMaterial{
        CG::ShaderInfo{ GL_VERTEX_SHADER, "../media/shaders/texturePhong/phong.vert", true, 0 },
        CG::ShaderInfo{ GL_FRAGMENT_SHADER, "../media/shaders/texturePhong/phong.frag", true, 0 }
    };

    phongMat.setShininess(1000.0);

    phongMat.setUniformDataFunction([](const CG::OpenGLMaterial &material){
        glUniform4fv(material.getUniform("baseColor"), 1, material.getColor().data());
        glUniform1f(material.getUniform("shininess"), material.getShininess());
    });

    phongMat.addTexture(std::shared_ptr<CG::OpenGLTexture>{ new CG::OpenGLTexture("../media/textures/earth.jpg")});

    return phongMat;
}

CG::OpenGLMaterial setUpSkyBoxMaterial(std::shared_ptr<CG::OpenGLTexture> tex){
    CG::OpenGLMaterial skyBoxMat = CG::OpenGLMaterial{
        CG::ShaderInfo{ GL_VERTEX_SHADER, "../media/shaders/skyBox/skyBox.vert", true, 0 },
        CG::ShaderInfo{ GL_FRAGMENT_SHADER, "../media/shaders/skyBox/skyBox.frag", true, 0 }
    };

    skyBoxMat.addTexture(tex);

    return skyBoxMat;
}

CG::OpenGLMaterial setUpEnvMapMaterial(std::shared_ptr<CG::OpenGLTexture> tex){
    CG::OpenGLMaterial envMap = CG::OpenGLMaterial{
        CG::ShaderInfo{ GL_VERTEX_SHADER, "../media/shaders/envMap/envMap.vert", true, 0 },
        CG::ShaderInfo{ GL_FRAGMENT_SHADER, "../media/shaders/envMap/envMap.frag", true, 0 }
    };

    envMap.addTexture(tex);

    return envMap;
}

#endif