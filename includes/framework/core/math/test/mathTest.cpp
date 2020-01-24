#include <gtest/gtest.h>
#include "../math.h"

TEST(CG_Math_Test, createIdentityMatrix){
    CG::Matrix4 identity{ CG::createIdentityMatrix() };

    for(int row = 0; row < 4; ++row){
        for(int col = 0; col < 4; ++col){
            if(row == col){
                EXPECT_FLOAT_EQ(identity.at(row, col), 1.0);
            } else {
                EXPECT_FLOAT_EQ(identity.at(row, col), 0.0);
            }
        }
    }
}

TEST(CG_Math_Test, createTranslationMatrix){
    CG::Matrix4 translate{ CG::createTranslationMatrix(CG::Vector3{ 1.0, 2.0, 3.0 }) };

    for(int row = 0; row < 4; ++row){
        for(int col = 0; col < 4; ++col){
            if(row == col){
                EXPECT_FLOAT_EQ(translate.at(row, col), 1.0);
            } else {
                if(col < 3){
                    EXPECT_FLOAT_EQ(translate.at(row, col), 0.0);
                }else{
                    EXPECT_FLOAT_EQ(translate.at(row, col), row + 1);
                }
            }
        }
    }
}

//TODO: create tests for rest of the functions