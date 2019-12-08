#include "../matrix.h"
#include <iostream>
#include <gtest/gtest.h>

TEST(Matrix_TEST, initializer_list_constructor)
{
    CG::LinAlg::Matrix<float, 2, 2> mat{ {1.0, 2.0}, {3.0, 4.0} };

    float* matPtr = mat;
    EXPECT_EQ(matPtr[0], 1.0);
    EXPECT_EQ(matPtr[1], 3.0);
    EXPECT_EQ(matPtr[2], 2.0);
    EXPECT_EQ(matPtr[3], 4.0);
}