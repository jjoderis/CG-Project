#include "../vector.h"
#include <iostream>
#include <gtest/gtest.h>

TEST(VECTOR_TEST, initializer_list_constructor)
{
    CG::LinAlg::Vector<float, 3> vec{ 1.0 , 2.0, 3.0};

    float* vecPtr = vec;
    EXPECT_EQ(vecPtr[0], 1.0);
    EXPECT_EQ(vecPtr[1], 2.0);
    EXPECT_EQ(vecPtr[2], 3.0); 
}

TEST(VECTOR_TEST, copy_constructor)
{
    CG::LinAlg::Vector<float, 4> origVec{ 1.0, 2.0, 3.0, 4.0 };
    CG::LinAlg::Vector<float, 4> copyVec{ origVec };

    EXPECT_EQ(origVec, copyVec);
}

TEST(VECTOR_TEST, smaller_vector_constructor)
{
    CG::LinAlg::Vector<int, 3> vec3{ 1, 2, 3 };

    CG::LinAlg::Vector<int, 4> vec4{ vec3, 10 };

    CG::LinAlg::Vector<int, 4> res{ 1, 2, 3, 10 };

    EXPECT_EQ(vec4, res);
}

TEST(VECTOR_TEST, at_function)
{
    CG::LinAlg::Vector<int, 3> vec3{ 1, 2, 3 };

    EXPECT_EQ(vec3.at(0), 1);
    EXPECT_EQ(vec3.at(1), 2);
    EXPECT_EQ(vec3.at(2), 3);
}

TEST(VECTOR_TEST, assignment_overload)
{
    CG::LinAlg::Vector<float, 2> vec{ 0.0, 0.0 };

    CG::LinAlg::Vector<float, 2> assignVec{ 2.0, 2.0 };
    vec = assignVec;

    EXPECT_EQ(vec, assignVec);
}

TEST(VECTOR_TEST, decay_to_array)
{
    CG::LinAlg::Vector<float, 3> vec{ 1.0 , 2.0, 3.0};

    float* vecDataPtr = vec;

    EXPECT_EQ(*vecDataPtr, 1.0);
    EXPECT_EQ(*(vecDataPtr + 1), 2.0);  
    EXPECT_EQ(*(vecDataPtr + 2), 3.0);
}

TEST(VECTOR_TEST, outstream_overload)
{
    CG::LinAlg::Vector<float, 3> vec{ 1.0 , 2.0, 3.0};

    testing::internal::CaptureStdout();
    std::cout << vec;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string{"[ 1, 2, 3 ]"});
}

TEST(VECTOR_TEST, add_overload)
{
   CG::LinAlg::Vector<float, 3> vec1{ 1.0 , 2.0, 3.0};
   CG::LinAlg::Vector<float, 3> vec2{ 1.0 , 2.0, 3.0};

   CG::LinAlg::Vector<float, 3> sum{ 2.0, 4.0, 6.0 };
   EXPECT_EQ(vec1 + vec2, sum); 
}

TEST(VECTOR_TEST, add_assign_overload)
{
    CG::LinAlg::Vector<float, 3> vec1{ 1.0 , 2.0, 3.0};
    vec1 += CG::LinAlg::Vector<float, 3>{ 1.0 , 2.0, 3.0};

    CG::LinAlg::Vector<float, 3> sum{ 2.0, 4.0, 6.0 };
    EXPECT_EQ(vec1, sum);
}

TEST(VECTOR_TEST, add_T_right)
{
    CG::LinAlg::Vector<int, 2> vec{ 0, 0 };

    CG::LinAlg::Vector<int, 2> ones{ 1, 1 };

    EXPECT_EQ(vec + 1, ones);
}

TEST(VECTOR_TEST, add_T_left)
{
    CG::LinAlg::Vector<int, 2> vec{ 0, 0 };

    CG::LinAlg::Vector<int, 2> ones{ 1, 1 };

    EXPECT_EQ(1 + vec, ones);
}

TEST(VECTOR_TEST, add_assign_T)
{
    CG::LinAlg::Vector<int, 2> vec{ 0, 0 };

    CG::LinAlg::Vector<int, 2> ones{ 1, 1 };

    vec += 1;

    EXPECT_EQ(vec, ones);
}

TEST(VECTOR_TEST, sub_overload)
{
   CG::LinAlg::Vector<int, 3> vec1{ 1, 2, 3 };
   CG::LinAlg::Vector<int, 3> vec2{ 1, 2, 3 };

   CG::LinAlg::Vector<int, 3> diff{ 0, 0, 0 };
   EXPECT_EQ(vec1 - vec2, diff); 
}

TEST(VECTOR_TEST, sub_assign_overload)
{
    CG::LinAlg::Vector<int, 3> vec1{ 1, 2, 3 };
    vec1 -= CG::LinAlg::Vector<int, 3>{ 1, 2, 3 };

    CG::LinAlg::Vector<int, 3> diff{ 0, 0, 0 };
    EXPECT_EQ(vec1, diff);
}

TEST(VECTOR_TEST, sub_T_right)
{
    CG::LinAlg::Vector<int, 2> vec{ 1, 1 };

    CG::LinAlg::Vector<int, 2> zeros{ 0, 0 };

    EXPECT_EQ(vec - 1, zeros);
}

TEST(VECTOR_TEST, sub_T_left)
{
    CG::LinAlg::Vector<int, 2> vec{ 1, 1 };

    CG::LinAlg::Vector<int, 2> zeros{ 0, 0 };

    EXPECT_EQ(1 - vec, zeros);
}

TEST(VECTOR_TEST, sub_assign_T)
{
    CG::LinAlg::Vector<int, 2> vec{ 1, 1 };

    CG::LinAlg::Vector<int, 2> zeros{ 0, 0 };

    vec -= 1;

    EXPECT_EQ(vec, zeros);
}

TEST(VECTOR_TEST, unary_sub_overload)
{
    CG::LinAlg::Vector<int, 3> vec{  1, -10,  2};

    CG::LinAlg::Vector<int, 3> inv{ -1,  10, -2};

    EXPECT_EQ(-vec, inv);
}

TEST(VECTOR_TEST, mult_overload)
{
    CG::LinAlg::Vector<int, 2> vec{ 2, 3 };

    CG::LinAlg::Vector<int, 2> square{ 4, 9 };

    EXPECT_EQ(vec * vec, square);
}

TEST(VECTOR_TEST, mult_assign_overload)
{
    CG::LinAlg::Vector<int, 2> vec{ 2, 3 };

    CG::LinAlg::Vector<int, 2> square{ 4, 9 };

    vec *= vec;

    EXPECT_EQ(vec, square);
}

TEST(VECTOR_TEST, mult_T_right)
{
    CG::LinAlg::Vector<int, 2> vec{ 1, 1 };

    CG::LinAlg::Vector<int, 2> twos{ 2, 2 };

    EXPECT_EQ(vec * 2, twos);
}

TEST(VECTOR_TEST, mult_T_left)
{
    CG::LinAlg::Vector<int, 2> vec{ 1, 1 };

    CG::LinAlg::Vector<int, 2> twos{ 2, 2 };

    EXPECT_EQ(2 * vec, twos);
}

TEST(VECTOR_TEST, mult_assign_T)
{
    CG::LinAlg::Vector<int, 2> vec{ 1, 1 };

    CG::LinAlg::Vector<int, 2> twos{ 2, 2 };

    vec *= 2;

    EXPECT_EQ(vec, twos);
}

TEST(VECTOR_TEST, div_overload)
{
    CG::LinAlg::Vector<int, 2> vec{ 4, 9 };

    CG::LinAlg::Vector<int, 2> ones{ 1, 1 };

    EXPECT_EQ(vec / vec, ones);
}

TEST(VECTOR_TEST, div_assign_overload)
{
    CG::LinAlg::Vector<int, 2> vec{ 2, 3 };

    CG::LinAlg::Vector<int, 2> ones{ 1, 1 };

    vec /= vec;

    EXPECT_EQ(vec, ones);
}

TEST(VECTOR_TEST, div_T_right)
{
    CG::LinAlg::Vector<int, 2> vec{ 3, 9 };

    CG::LinAlg::Vector<int, 2> quot{ 1, 3 };

    EXPECT_EQ(vec / 3, quot);
}

TEST(VECTOR_TEST, div_T_left)
{
    CG::LinAlg::Vector<int, 2> vec{ 9, 3 };

    CG::LinAlg::Vector<int, 2> quot{ 1, 3 };

    EXPECT_EQ(9 / vec, quot);
}

TEST(VECTOR_TEST, div_assign_T)
{
    CG::LinAlg::Vector<int, 2> vec{ 10, 20 };

    CG::LinAlg::Vector<int, 2> quot{ 2, 4 };

    vec /= 5;

    EXPECT_EQ(vec, quot);
}

TEST(VECTOR_TEST, dot_product)
{
    CG::LinAlg::Vector<int, 3> vec1{ 1, 0, 0 };
    CG::LinAlg::Vector<int, 3> vec2{ 0, 1, 0 };

    ASSERT_FLOAT_EQ(vec1.dot(vec2), 0.0);
    ASSERT_FLOAT_EQ(vec1.dot(vec1), 1.0);
}

TEST(VECTOR_TEST, length)
{
    CG::LinAlg::Vector<int, 3> vec1{ 1, 0, 0 };
    CG::LinAlg::Vector<int, 3> vec2{ 2, 0, 0 };

    ASSERT_FLOAT_EQ(vec1.length(), 1.0);
    ASSERT_FLOAT_EQ(vec2.length(), 2.0);
}

TEST(VECTOR_TEST, angleTo)
{
    CG::LinAlg::Vector<int, 3> vec1{ 1, 0, 0 };
    CG::LinAlg::Vector<int, 3> vec2{ 0, 1, 0 };

    ASSERT_FLOAT_EQ(180*vec1.angleTo(vec1)/M_PI, 0.0);
    ASSERT_FLOAT_EQ(180*vec1.angleTo(vec2)/M_PI, 90.0);
}

TEST(VECTOR_TEST, allClose)
{
    CG::LinAlg::Vector<float, 3> vec1{ 0.1, 0.1, 0.1 };
    CG::LinAlg::Vector<float, 3> vec2{ 1.0, 1.0, 1.0 };

    CG::LinAlg::Vector<float, 3> roundErr{ 0.0, 0.0, 0.0 };

    for(int i = 0; i < 10; ++i){
        roundErr += vec1;
    }

    ASSERT_NE(roundErr, vec2);
    ASSERT_TRUE(vec2.allClose(roundErr));
}

TEST(VECTOR_TEST, normalize)
{
    CG::LinAlg::Vector<float, 3> vec{ 2.3, 5.6, 1.7 };

    vec.normalize();
    ASSERT_FLOAT_EQ(vec.length(), 1.0);
}

TEST(VECTOR_TEST, orthogonal_projection)
{
    CG::LinAlg::Vector<float, 2> a{ 1, 2 };
    CG::LinAlg::Vector<float, 2> b{ 3, 4 };

    CG::LinAlg::Vector<float, 2> proj = orthogonalProject(a, b);
    CG::LinAlg::Vector<float, 2> expected{ 1.32, 1.76 };

    ASSERT_TRUE(proj.allClose(expected));
}

TEST(VECTOR_TEST, cross_product)
{
    CG::LinAlg::Vector<int, 3> u{ 1, 0, 0 };
    CG::LinAlg::Vector<int, 3> v{ 0, 1, 0 };

    CG::LinAlg::Vector<int, 3> expected{ 0, 0, 1 };

    ASSERT_EQ(cross(u, v), expected);
}