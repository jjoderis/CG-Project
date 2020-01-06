#include "math.h"

CG::Matrix4 CG::createIdentityMatrix(){
    return Matrix4{
        { 1.0, 0.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };
}

CG::Matrix4 CG::createTranslationMatrix(CG::Vector3 &translation){
    return Matrix4{
        { 1.0, 0.0, 0.0, translation.at(0) },
        { 0.0, 1.0, 0.0, translation.at(1) },
        { 0.0, 0.0, 1.0, translation.at(2) },
        { 0.0, 0.0, 0.0, 1.0 }
    };
}

CG::Matrix4 CG::createScalingMatrix(Vector3 &scaling){
    return Matrix4{
        { scaling.at(0), 0.0, 0.0, 0.0 },
        { 0.0, scaling.at(1), 0.0, 0.0 },
        { 0.0, 0.0, scaling.at(2), 0.0 },
        { 0.0, 0.0, 0.0, 1.0}
    };
}

CG::Matrix4 CG::createRotationMatrix(){
    return createIdentityMatrix();
}