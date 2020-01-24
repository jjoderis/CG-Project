#ifndef CG_EXAMPLES_SETUPCGSTUFF_H
#define CG_EXAMPLES_SETUPCGSTUFF_H

#include <OpenGL/scene/OpenGLScene.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>

#include "animations/animations.h"
#include "material/phong.h"

void setUpRenderer(CG::Renderer &renderer);

void setUp(CG::OpenGLScene &scene, CG::Camera &camera, CG::Renderer &renderer){
    (void)renderer;

    std::shared_ptr<CG::OpenGLSphereGeometry> spherePtr{ new CG::OpenGLSphereGeometry{ 1.0, 30, 30 } };
    spherePtr->activateNormals();
    spherePtr->activateUVs();
    spherePtr->updateOpenGL();

    CG::OpenGLMaterial phong{ setUpPhongMaterial() };

    std::shared_ptr<CG::OpenGLMesh> redSphere = std::make_shared<CG::OpenGLMesh>();
    redSphere->setMaterial(phong);
    redSphere->setGeometry(spherePtr);
    redSphere->getMaterial()->setColor(1.0, 0.0, 0.0);
    redSphere->setAnimation(rotateAroundY);
    redSphere->translate(0.0, 1.0, 0.0);
    redSphere->updateMatrixWorld();

    scene.addChild(redSphere);

    camera.setPosition(3.0, 1.0, 0.0);
    camera.rotateY(degToRad(90));
    camera.updateMatrixWorld();
}
#endif