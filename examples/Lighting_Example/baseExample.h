#ifndef CG_EXAMPLES_LIGHTING_BASE_H
#define CG_EXAMPLES_LIGHTING_BASE_H

#include <OpenGL/scene/OpenGLScene.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>

#include "animations/bounceAround.h"
#include "geometry/box.h"
#include "material/phong.h"
#include <core/light/pointLight/pointLight.h>

void setUpRenderer(CG::Renderer &renderer);

void setUp(CG::OpenGLScene &scene, CG::Camera &camera, CG::Renderer &renderer){
    (void)renderer;

    std::shared_ptr<CG::OpenGLSphereGeometry> spherePtr{ new CG::OpenGLSphereGeometry{ 1.0, 30, 30 } };
    std::shared_ptr<CG::OpenGLGeometry> boxPtr = std::make_shared<CG::OpenGLGeometry>(setUpBoxGeometry());

    CG::OpenGLMaterial phong{ setUpPhongMaterial() };
    CG::OpenGLMaterial plainYellow{ CG::RGBA_Color{ 1.0, 1.0, 0.0, 1.0 } };

    std::shared_ptr<CG::OpenGLMesh> redSphere = std::make_shared<CG::OpenGLMesh>();
    redSphere->setMaterial(phong);
    redSphere->setGeometry(spherePtr);
    redSphere->getMaterial()->setColor(1.0, 0.0, 0.0);
    redSphere->setAnimation(bounceAround);
    redSphere->setVelocity(CG::Vector3{0.1, 0.2, 0.08}.normalize() * 0.2f);

    std::shared_ptr<CG::OpenGLMesh> greenSphere = std::make_shared<CG::OpenGLMesh>();
    greenSphere->setMaterial(phong);
    greenSphere->setGeometry(spherePtr);
    greenSphere->getMaterial()->setColor(0.0, 1.0, 0.0);
    greenSphere->setAnimation(bounceAround);
    greenSphere->setVelocity(CG::Vector3{0.04, 0.3, 0.2}.normalize() * 0.2f);
    std::shared_ptr<CG::OpenGLMesh> yellowCubeOutline = std::make_shared<CG::OpenGLMesh>();
    yellowCubeOutline->setGeometry(boxPtr);
    yellowCubeOutline->setMaterial(plainYellow);

    scene.addChild(redSphere);
    scene.addChild(greenSphere);
    scene.addChild(yellowCubeOutline);

    std::shared_ptr<CG::Light> light2{ new CG::PointLight{CG::Vector4{ 10.0, 0.0, 0.0, 1.0 }} };
    scene.addLight(light2);

    camera.setPosition(15.0, 0.0, 0.0);
    camera.rotateY(degToRad(90));
    camera.updateMatrixWorld();
}
#endif