#include "../vector.h"

#include <gtest/gtest.h>

TEST(VECTEST, constructor)
{
    CG::LinAlg::Vector<float, 3> vec{ 1.0 , 1.0, 1.0};
    CG::LinAlg::Vector<float, 3> vec2{2.0, 1.0, 1.0};

    EXPECT_EQ(vec, vec2);
}