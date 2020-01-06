#ifndef CG_FRAMEWORK_CORE_MATH_MATH_H
#define CG_FRAMEWORK_CORE_MATH_MATH_H

#include <GL/glew.h>
#include <LinAlg/vector/vector.h>
#include <LinAlg/matrix/matrix.h>

namespace CG{

    using Vector2 = LinAlg::Vector<GLfloat, 2>;
    using Vector3 = LinAlg::Vector<GLfloat, 3>;
    using Vector4 = LinAlg::Vector<GLfloat, 4>;

    using IVector2 = LinAlg::Vector<GLint, 2>;
    using IVector3 = LinAlg::Vector<GLint, 3>;
    using IVector4 = LinAlg::Vector<GLint, 4>;

    using DVector2 = LinAlg::Vector<GLdouble, 2>;
    using DVector3 = LinAlg::Vector<GLdouble, 3>;
    using DVector4 = LinAlg::Vector<GLdouble, 4>;

    using Matrix2 = LinAlg::Matrix<GLfloat, 2, 2>;
    using Matrix3 = LinAlg::Matrix<GLfloat, 3, 3>;
    using Matrix4 = LinAlg::Matrix<GLfloat, 4, 4>;

    Matrix4 createIdentityMatrix();
    Matrix4 createTranslationMatrix(Vector3 &translation);
    Matrix4 createRotationMatrix();
    Matrix4 createScalingMatrix(Vector3 &scaling);
}

#endif