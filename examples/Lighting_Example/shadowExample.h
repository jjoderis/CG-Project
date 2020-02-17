#ifndef CG_EXAMPLES_LIGHTING_SHADOW_H
#define CG_EXAMPLES_LIGHTING_SHADOW_H

#include <OpenGL/scene/OpenGLScene.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>

#include "animations/bounceAround.h"
#include "geometry/box.h"
#include "material/phong.h"
#include <core/light/pointLight/pointLight.h>
#include <OpenGL/geometry/boxGeometry/OpenGLBoxGeometry.h>
#include <chrono>

void setUpRenderer(CG::Renderer &renderer);

void setUp(CG::OpenGLScene &scene, CG::Camera &camera, CG::Renderer &renderer){
    (void)renderer;

    std::shared_ptr<CG::OpenGLSphereGeometry> spherePtr{ new CG::OpenGLSphereGeometry{ 1.0, 30, 30 } };
    std::shared_ptr<CG::OpenGLGeometry> boxPtr{ new CG::OpenGLGeometry{
        {
            { -1.0, -5.0, -5.0 },
            { -1.0, -5.0, 5.0 },
            { -1.0, 5.0, 5.0 },
            { -1.0, 5.0, -5.0 }
        },
        {
            { 2, 1, 0 },
            { 3, 2, 0 }
        }
    }};

    CG::OpenGLMaterial phong = CG::OpenGLMaterial{
        CG::ShaderInfo{ GL_VERTEX_SHADER, "../media/shaders/lighting/lighting.vert", true, 0 },
        CG::ShaderInfo{ GL_FRAGMENT_SHADER, "../media/shaders/lighting/lighting.frag", true, 0 }
    };

    phong.setShininess(120.0);

    CG::OpenGLMaterial plainWhite{
        CG::ShaderInfo{ GL_VERTEX_SHADER, "../media/shaders/lighting/lighting.vert", true, 0 },
        CG::ShaderInfo{ GL_FRAGMENT_SHADER, "../media/shaders/lighting/lighting.frag", true, 0 }
    };

    plainWhite.setShininess(3);

    std::shared_ptr<CG::OpenGLMesh> redSphere = std::make_shared<CG::OpenGLMesh>();
    redSphere->setMaterial(phong);
    redSphere->setGeometry(spherePtr);
    redSphere->getMaterial()->setColor(1.0, 0.0, 0.0);

    std::shared_ptr<CG::OpenGLMesh> background = std::make_shared<CG::OpenGLMesh>();
    background->setGeometry(boxPtr);
    background->setMaterial(plainWhite);
    background->getMaterial()->setColor(1.0, 1.0, 1.0);

    scene.addChild(redSphere);
    scene.addChild(background);

    std::shared_ptr<CG::Light> light2{ new CG::PointLight{CG::Vector4{ 2.0, 0.0, 0.0, 1.0 }} };
    scene.addLight(light2);

    light2->setAnimation([](CG::Object3D &light) mutable {
        float ms = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
        ).count() % 3000 - 1500;

        light.setPosition(5.0, 5*sin(ms/1500*3.14), 1.4*sin(ms/750*3.14));
    });
    light2->isAnimated = true;

    camera.setPosition(15.0, 0.0, 0.0);
    camera.rotateY(degToRad(90));
    camera.updateMatrixWorld();
}
#endif