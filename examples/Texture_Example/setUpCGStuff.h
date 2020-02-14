#ifndef CG_EXAMPLES_SETUPCGSTUFF_H
#define CG_EXAMPLES_SETUPCGSTUFF_H

#include <OpenGL/scene/OpenGLScene.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>

#include "animations/animations.h"
#include "material/materials.h"
#include "geometry/box.h"
#include "geometry/sprites.h"

void setUpRenderer(CG::Renderer &renderer);

void setUp(CG::OpenGLScene &scene, CG::Camera &camera, CG::Renderer &renderer){
    (void)renderer;

    //Geometries
    std::shared_ptr<CG::OpenGLSphereGeometry> sphereGeoPtr{ new CG::OpenGLSphereGeometry{ 1.0, 100, 100 } };
    sphereGeoPtr->activateNormals();
    sphereGeoPtr->activateUVs();
    sphereGeoPtr->updateOpenGL();

    std::shared_ptr<CG::OpenGLGeometry> boxGeoPtr = std::make_shared<CG::OpenGLGeometry>(setUpBox());

    std::shared_ptr<CG::OpenGLGeometry> pointGeometry = std::make_shared<CG::OpenGLGeometry>(setUpSnowFlakes());

    //Textures
    std::shared_ptr<CG::OpenGLTexture> cubeMapTexture { new CG::OpenGLTexture(GL_TEXTURE_CUBE_MAP, 0, "../media/textures/cube.jpg")};
    std::shared_ptr<CG::OpenGLTexture> snowFlakeTexture{ new CG::OpenGLTexture(GL_TEXTURE_2D, 0, "../media/textures/snowflake.jpg")};

    //Material
    //std::shared_ptr<CG::OpenGLMaterial> cubeMapPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{ setUpPhongMaterial() });

    std::shared_ptr<CG::OpenGLMaterial> boxMatPtr = std::make_shared<CG::OpenGLMaterial>(setUpSkyBoxMaterial(cubeMapTexture));

    std::shared_ptr<CG::OpenGLMaterial> envMapPtr = std::make_shared<CG::OpenGLMaterial>(setUpEnvMapMaterial(cubeMapTexture));

    std::shared_ptr<CG::OpenGLMaterial> flakeMatPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{
        CG::ShaderInfo{ GL_VERTEX_SHADER, "../media/shaders/sprite/sprite.vert", true, 0 },
        CG::ShaderInfo{ GL_FRAGMENT_SHADER, "../media/shaders/sprite/sprite.frag", true, 0 }
    });
    flakeMatPtr->addTexture(snowFlakeTexture);


    std::shared_ptr<CG::OpenGLMesh> sphereMesh = std::make_shared<CG::OpenGLMesh>(CG::OpenGLMesh(sphereGeoPtr, envMapPtr));
    sphereMesh->getMaterial()->setColor(1.0, 0.0, 0.0);
    sphereMesh->setAnimation(rotateAroundY);

    sphereMesh->beforeRender = [](const CG::OpenGLMesh &mesh, const CG::Matrix4 &viewMatrix, const CG::Matrix4 &viewMatrixInverse, const CG::Matrix4 &projectionMatrix){
        glUniformMatrix4fv(mesh.getMaterial()->getUniform("viewMatrixInverse"), 1, GL_FALSE, viewMatrixInverse.data());
    };

    scene.addChild(sphereMesh);

    std::shared_ptr<CG::OpenGLMesh> boxPtr = std::make_shared<CG::OpenGLMesh>(CG::OpenGLMesh{ boxGeoPtr, boxMatPtr });
    boxPtr->scale(20.0);
    boxPtr->updateMatrixWorld();

    scene.addChild(boxPtr);

    std::shared_ptr<CG::OpenGLMesh> snowPtr = std::make_shared<CG::OpenGLMesh>(CG::OpenGLMesh{ pointGeometry, flakeMatPtr });

    scene.addChild(snowPtr);

    camera.setPosition(3.0, 0.0, 0.0);
    camera.rotateY(degToRad(90));
    camera.updateMatrixWorld();

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SPRITE);
}
#endif