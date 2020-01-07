#ifndef CG_FRAMEWORK_MATH_MATH_H
#define CG_FRAMEWORK_MATH_MATH_H

#include <GL/glew.h>
#include <LinAlg/vector/vector.h>
#include <LinAlg/matrix/matrix.h>

//Helper functions
float degToRad(float deg);
float radToDeg(float rad);
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
    Matrix4 createTranslationMatrix(const Vector3 &translation);
    Matrix4 createRotationMatrixX(GLfloat xRot);
    Matrix4 createRotationMatrixY(GLfloat yRot);
    Matrix4 createRotationMatrixZ(GLfloat zRot);
    Matrix4 createScalingMatrix(const Vector3 &scaling);

    //sheared denotes index of coordinate to be shear (e.g. 0 = x); shearing denotes axis which does shearing
    Matrix4 createShearingMatrix(int sheared, int shearing, float amount);
}

#endif