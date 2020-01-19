#include <OpenGL/scene/OpenGLScene.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>

#include "scene/sphere.h"
#include "scene/box.h"

void setUpRenderer(CG::Renderer &renderer);

void setUp(CG::OpenGLScene &scene, CG::Camera &camera, CG::Renderer &renderer){
    (void)camera;
    (void)renderer;

    setUpSphere(scene);
    setUpBox(scene);

    setUpRenderer(renderer);
}

void setUpRenderer(CG::Renderer &renderer){
    
    renderer.setRenderFunction([](CG::Renderer &renderer, CG::OpenGLScene &scene, CG::Camera &camera){
        (void)renderer;

        glClearBufferfv(GL_COLOR, 0, scene.getBackground().data());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        CG::Matrix4 viewMatrix = camera.getMatrixWorldInverse();
        CG::Matrix4 viewMatrixInverse = camera.getMatrixWorld();
        CG::Matrix4 projectionMatrix = camera.getProjectionMatrix();

        for(const std::shared_ptr<CG::OpenGLMesh> &mesh : scene.getChildren()){

            if(mesh->isAnimated){
                mesh->animate();
            }

            mesh->render(viewMatrix, viewMatrixInverse, projectionMatrix);
        }
    });

}