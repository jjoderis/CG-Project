#include <OpenGL/scene/OpenGLScene.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>

#include "scene/sphere.h"
#include "scene/box.h"
#include "scene/particles.h"

void setUpRenderer(CG::Renderer &renderer);

void setUp(CG::OpenGLScene &scene, CG::Camera &camera, CG::Renderer &renderer){
    (void)camera;
    (void)renderer;

    setUpSphere(scene);
    setUpParticles(scene);
    //setUpBox(scene);

    setUpRenderer(renderer);
}

void setUpRenderer(CG::Renderer &renderer){

    unsigned int transFeed{ 0 };
    glCreateTransformFeedbacks(1, &transFeed);

    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transFeed);

    renderer.getTransformFeedbacks().emplace_back(transFeed);
    
    renderer.setRenderFunction([](CG::Renderer &renderer, CG::OpenGLScene &scene, CG::Camera &camera){
        (void)renderer;

        glClearBufferfv(GL_COLOR, 0, scene.getBackground().data());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        CG::Matrix4 viewMatrix = camera.getMatrixWorldInverse();
        CG::Matrix4 viewMatrixInverse = camera.getMatrixWorld();
        CG::Matrix4 projectionMatrix = camera.getProjectionMatrix();

        int frameCount = renderer.getFrameCount();

        std::vector<float> data(3*2*100);

        for(const std::shared_ptr<CG::OpenGLMesh> &mesh : scene.getChildren()){

            if(mesh->isAnimated){
                mesh->animate();
            }

            mesh->render(viewMatrix, viewMatrixInverse, projectionMatrix);

            glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, scene.getParticles()[((frameCount+1) % 2)]->getGeometry()->getVBO());
            scene.getParticles()[frameCount]->render(viewMatrix, viewMatrixInverse, projectionMatrix);
            glBeginTransformFeedback(GL_POINTS);
            glDrawArrays(GL_POINTS, 0, 100);
            glEndTransformFeedback();
        }

        glGetNamedBufferSubData(scene.getParticles()[frameCount]->getGeometry()->getVBO(), 0, 3*2*100*sizeof(float), data.data());

        renderer.setFrameCounter((frameCount + 1) % 2);
    });

}