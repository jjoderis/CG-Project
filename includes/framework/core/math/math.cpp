#include "math.h"

CG::Matrix4 CG::createIdentityMatrix(){
    return Matrix4{
        { 1.0, 0.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };
}

CG::Matrix4 CG::createTranslationMatrix(const CG::Vector3 &translation){
    return Matrix4{
        { 1.0, 0.0, 0.0, translation.at(0) },
        { 0.0, 1.0, 0.0, translation.at(1) },
        { 0.0, 0.0, 1.0, translation.at(2) },
        { 0.0, 0.0, 0.0, 1.0 }
    };
}

CG::Matrix4 CG::createScalingMatrix(const Vector3 &scaling){
    return Matrix4{
        { scaling.at(0), 0.0, 0.0, 0.0 },
        { 0.0, scaling.at(1), 0.0, 0.0 },
        { 0.0, 0.0, scaling.at(2), 0.0 },
        { 0.0, 0.0, 0.0, 1.0}
    };
}

CG::Matrix4 CG::createRotationMatrixX(float xRot){
    return Matrix4{
        { 1.0, 0.0, 0.0, 0.0 },
        { 0.0, cos(xRot), -sin(xRot), 0.0 },
        { 0.0, sin(xRot), cos(xRot), 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };
}
CG::Matrix4 CG::createRotationMatrixY(float yRot){
    return Matrix4{
        { cos(yRot), 0.0, sin(yRot), 0.0 },
        { 0.0, 1.0, 0.0, 0.0 },
        { -sin(yRot), 0.0, cos(yRot), 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };
}
CG::Matrix4 CG::createRotationMatrixZ(float zRot){
    return Matrix4{
        { cos(zRot), -sin(zRot), 0.0, 0.0 },
        { sin(zRot), cos(zRot), 0.0, 0.0},
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };
}

CG::Matrix4 CG::createShearingMatrix(int sheared, int shearing, float amount){
    Matrix4 shearMat{ createIdentityMatrix() };
    if(sheared == shearing){
        return shearMat;
    }
    shearMat.at(sheared, shearing) = amount;
    return shearMat;
}

CG::Matrix4 CG::lookAt(const Vector3 &worldPos, const Vector3 &direction, const Vector3 &up){
    Vector3 view{(worldPos - direction).normalize()};

    Vector3 right{-(cross(view, up).normalize())};

    Vector3 upNew = cross(view, right);

    return {
        { right.at(0), right.at(1), right.at(2), -(float)LinAlg::dot(worldPos, right) },
        { upNew.at(0), upNew.at(1), upNew.at(2), -(float)LinAlg::dot(worldPos, upNew) },
        { view.at(0), view.at(1), view.at(2), -(float)LinAlg::dot(worldPos, view) },
        { 0.0, 0.0, 0.0, 1.0 }
    };
}

CG::Matrix4 CG::perspective(float fov, float aspect, float near, float far){
    float c{ 1.0f/tan(fov/2) };
    return {
        { c/aspect, 0.0, 0.0, 0.0},
        { 0.0, c, 0.0, 0.0},
        { 0.0, 0.0, -((far+near)/(far-near)), -((2*far*near)/(far*near))},
        { 0.0, 0.0, -1.0, 0.0 }
    };
}

float degToRad(float deg){
    return M_PI * (deg / 180.0f);
}

float radToDeg(float rad){
    return 180 * (rad / M_PI);
}