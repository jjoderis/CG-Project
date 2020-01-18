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

    void renderScene(Renderer &renderer, Scene &scene, Camera &camera);
    void renderMesh(Renderer &renderer, const Mesh *mesh, const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix);

    //A class used to render a given scene
    class Renderer{

    GLenum m_drawMode{ GL_TRIANGLES };

    std::vector<unsigned int> m_tranformFeedbacks{};

    void(*m_renderFunction)(Renderer &renderer, Scene &scene, Camera &camera){renderScene};
    
    public:
        Renderer();

        //renders the given scene using the given camera
        void render(Scene &scene, Camera &camera);

        void setDrawMode(GLenum drawMode);
        GLenum getDrawMode() const;

        void setRenderFunction(void(*renderFunction)(Renderer &renderer, Scene &scene, Camera &camera));

        std::vector<unsigned int>& getTransformFeedbacks();
    };

}

#endif