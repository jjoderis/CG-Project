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

CG::Matrix4 CG::createRotationMatrixX(GLfloat xRot){
    return Matrix4{
        { 1.0, 0.0, 0.0, 0.0 },
        { 0.0, cos(xRot), -sin(xRot), 0.0 },
        { 0.0, sin(xRot), cos(xRot), 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };
}
CG::Matrix4 CG::createRotationMatrixY(GLfloat yRot){
    return Matrix4{
        { cos(yRot), 0.0, sin(yRot), 0.0 },
        { 0.0, 1.0, 0.0, 0.0 },
        { -sin(yRot), 0.0, cos(yRot), 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };
}
CG::Matrix4 CG::createRotationMatrixZ(GLfloat zRot){
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

float degToRad(float deg){
    return M_PI * (deg / 180.0f);
}

float radToDeg(float rad){
    return 180 * (rad / M_PI);
}