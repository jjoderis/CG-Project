#ifndef CG_FRAMEWORK_CORE_RENDERER_RENDERER_H
#define CG_FRAMEWORK_CORE_RENDERER_RENDERER_H

#include <GL/glew.h>
#include <OpenGL/scene/OpenGLScene.h>
#include <camera/camera.h>
#include <OpenGL/material/OpenGLMaterial.h>
#include <OpenGL/geometry/OpenGLGeometry.h>
#include <memory>

namespace CG{
    class Renderer;

    void renderScene(Renderer &renderer, OpenGLScene &scene, Camera &camera);

    //A class used to render a given scene
    class Renderer{

    GLenum m_drawMode{ GL_TRIANGLES };

    std::vector<unsigned int> m_tranformFeedbacks{};

    int m_frameCounter{ 0 };

    void(*m_renderFunction)(Renderer &renderer, OpenGLScene &scene, Camera &camera){renderScene};
    
    public:
        Renderer();

        //renders the given scene using the given camera
        void render(OpenGLScene &scene, Camera &camera);

        void setDrawMode(GLenum drawMode);
        GLenum getDrawMode() const;

        void setRenderFunction(void(*renderFunction)(Renderer &renderer, OpenGLScene &scene, Camera &camera));

        std::vector<unsigned int>& getTransformFeedbacks();

        void increaseFrameCounter();
        void setFrameCounter(int count);
        int getFrameCount();
    };

}

#endif