#ifndef CG_FRAMEWORK_MATH_MATH_H
#define CG_FRAMEWORK_MATH_MATH_H

#include <LinAlg/vector/vector.h>
#include <LinAlg/matrix/matrix.h>

//Helper functions
float degToRad(float deg);
float radToDeg(float rad);
namespace CG{

    using Vector2 = LinAlg::Vector<float, 2>;
    using Vector3 = LinAlg::Vector<float, 3>;
    using Vector4 = LinAlg::Vector<float, 4>;

    using IVector2 = LinAlg::Vector<int, 2>;
    using IVector3 = LinAlg::Vector<int, 3>;
    using IVector4 = LinAlg::Vector<int, 4>;

    using DVector2 = LinAlg::Vector<double, 2>;
    using DVector3 = LinAlg::Vector<double, 3>;
    using DVector4 = LinAlg::Vector<double, 4>;

    using Matrix2 = LinAlg::Matrix<float, 2, 2>;
    using Matrix3 = LinAlg::Matrix<float, 3, 3>;
    using Matrix4 = LinAlg::Matrix<float, 4, 4>;

    Matrix4 createIdentityMatrix();
    Matrix4 createTranslationMatrix(const Vector3 &translation);
    Matrix4 createRotationMatrixX(float xRot);
    Matrix4 createRotationMatrixY(float yRot);
    Matrix4 createRotationMatrixZ(float zRot);
    Matrix4 createScalingMatrix(const Vector3 &scaling);

    //sheared denotes index of coordinate to be shear (e.g. 0 = x); shearing denotes axis which does shearing
    Matrix4 createShearingMatrix(int sheared, int shearing, float amount);

    Matrix4 lookAt(const Vector3 &worldPos, const Vector3 &direction, const Vector3 &up);
    Matrix4 perspective(float fov, float aspect, float near, float far);
}

#endif