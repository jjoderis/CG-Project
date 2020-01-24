#include <gtest/gtest.h>
#include "../object3D.h"

TEST(Object3D_Test, updateMatrixWorld){

    CG::Object3D obj{};

    obj.translate( 2.0, 3.0, 1.0 );
    obj.rotate({ 1.0, 0.0, 0.0}, degToRad(10));
    obj.scale(2.0);
    obj.updateMatrixWorld();

    CG::Matrix4 expectedMatrix{ CG::createTranslationMatrix({2.0, 3.0, 1.0}) *
                                CG::createRotationMatrix(CG::Quaternion{ 1.0, 0.0, 0.0, degToRad(10)}.normalize()) *
                                CG::createScalingMatrix({2.0, 2.0, 2.0})
                              };
    
    EXPECT_TRUE(obj.getMatrixWorld().allClose(expectedMatrix));
}