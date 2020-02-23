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

    //A class used to render a given scene
    class Renderer{

    GLenum m_drawMode{ GL_TRIANGLES };
    GLuint m_depthTexture{ 0 };
    GLuint m_depthFBO{ 0 };

    int m_shadowWidth{ 1024 };
    int m_shadowHeight{ 1024 };

    int m_screenWidth{ 800 };
    int m_screenHeight{ 600 };

    GLuint m_shadowProgram{ 0 };

    std::vector<unsigned int> m_tranformFeedbacks{};

    int m_frameCounter{ 0 };

    void renderMesh(OpenGLMesh &mesh , Matrix4 &viewMatrix, Matrix4 &viewMatrixInverse, Matrix4 &projectionMatrix);
    
    public:
        Renderer(int width, int height);

        //renders the given scene using the given camera
        void render(OpenGLScene &scene, Camera &camera);

        void setDrawMode(GLenum drawMode);
        GLenum getDrawMode() const;

        std::vector<unsigned int>& getTransformFeedbacks();

        void increaseFrameCounter();
        void setFrameCounter(int count);
        int getFrameCount();
    };

}

#endif