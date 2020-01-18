#ifndef CG_FRAMEWORK_OPENGL_MESH_OPENGLMESH_OPENGLMESH_H
#define CG_FRAMEWORK_OPENGL_MESH_OPENGLMESH_OPENGLMESH_H

#include <core/mesh/mesh.h>
#include <OpenGL/geometry/OpenGLGeometry.h>
#include <OpenGL/material/OpenGLMaterial.h>

namespace CG{
    using OpenGLMesh = Mesh<CG::OpenGLGeometry, CG::OpenGLMaterial>;
}

#endif