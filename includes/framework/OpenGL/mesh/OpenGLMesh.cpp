#include "OpenGLMesh.h"
#include <core/mesh/mesh.cpp>

template class CG::Mesh<CG::OpenGLGeometry, CG::OpenGLMaterial>;

template<>
void CG::Mesh<CG::OpenGLGeometry, CG::OpenGLMaterial>::render(const Matrix4 &viewMatrix, const Matrix4 &viewMatrixInverse, const Matrix4 &projectionMatrix){}