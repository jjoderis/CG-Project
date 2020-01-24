#ifndef CG_FRAMEWORK_OPENGL_MESH_OPENGLMESH_OPENGLMESH_H
#define CG_FRAMEWORK_OPENGL_MESH_OPENGLMESH_OPENGLMESH_H

#include <mesh/mesh.h>
#include <OpenGL/geometry/OpenGLGeometry.h>
#include <OpenGL/material/OpenGLMaterial.h>

namespace CG{
    using OpenGLMesh = Mesh<CG::OpenGLGeometry, CG::OpenGLMaterial>;

    template<>
    void CG::Mesh<CG::OpenGLGeometry, CG::OpenGLMaterial>::render(const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix);
}

#endif