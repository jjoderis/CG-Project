#ifndef CG_FRAMEWORK_CORE_RENDERER_RENDERER_H
#define CG_FRAMEWORK_CORE_RENDERER_RENDERER_H

#include <GL/glew.h>
#include <core/scene/scene.h>
#include <core/camera/camera.h>
#include <OpenGL/material/OpenGLMaterial.h>
#include <OpenGL/geometry/OpenGLGeometry.h>
#include <memory>

namespace CG{
    //A class used to render a given scene
    class Renderer{

    GLenum m_drawMode{ GL_TRIANGLES };

    void renderMesh(const CG::Mesh *mesh, const CG::Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const CG::Matrix4 &projectionMatrix) const;
    
    public:
        //renders the given scene using the given camera
        void render(const Scene &scene, const Camera &camera) const;
    };

}

#endif