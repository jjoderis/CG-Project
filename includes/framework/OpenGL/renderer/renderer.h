#ifndef CG_FRAMEWORK_CORE_RENDERER_RENDERER_H
#define CG_FRAMEWORK_CORE_RENDERER_RENDERER_H

#include <GL/glew.h>
#include <core/scene/scene.h>
#include <core/camera/camera.h>
#include <OpenGL/material/OpenGLMaterial.h>
#include <OpenGL/geometry/OpenGLGeometry.h>
#include <memory>

namespace CG{
    class Renderer;

    void renderMesh(const Renderer &renderer, const Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix);

    //A class used to render a given scene
    class Renderer{

    GLenum m_drawMode{ GL_TRIANGLES };

    unsigned int m_tranformFeedback{ 0 };

    void (*m_beforeAll)(const Renderer &renderer, Matrix4 &viewMatrix, Matrix4 &viewMatrixInverse, Matrix4 &projectionMatrix){ nullptr };
    void (*m_beforeRender)(const Renderer &renderer, const Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){ nullptr };
    void (*m_mainRender)(const Renderer &renderer, const Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){ renderMesh };
    void (*m_afterRender)(const Renderer &renderer, const Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){ nullptr };
    void (*m_afterAll)(const Renderer &renderer, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){ nullptr };
    
    public:
        Renderer();

        //renders the given scene using the given camera
        void render(const Scene &scene, const Camera &camera) const;

        void setDrawMode(GLenum drawMode);
        GLenum getDrawMode() const;

        void setBeforeAll(void (*beforeAll)(const Renderer &renderer, Matrix4 &viewMatrix, Matrix4 &viewMatrixInverse, Matrix4 &projectionMatrix));
        void deleteBeforeAll();

        void setBeforeRender(void (*beforeRender)(const Renderer &renderer, const Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix));
        void deleteBeforeRender();

        void setMainRender(void (*mainRender)(const Renderer &renderer, const Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix));
    
        void setAfterRender(void (*afterRender)(const Renderer &renderer, const Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix));
        void deleteAfterRender();
    
        void setAfterAll(void (*afterAll)(const Renderer &renderer, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix));
        void deleteAfterAll();

        unsigned int getTransformFeedback() const;
        void setTransformFeedback(unsigned int name);
    };

}

#endif