#include "../vector.h"
#include <iostream>
#include <gtest/gtest.h>

class VectorTest : public ::testing::Test {
    protected:
        // void SetUp() override {}

        // void TearDown() override {}
        LinAlg::Vector<int, 3> v1{ 1, 2, 3 };
};

TEST(VECTOR_TEST, instantiate_many_vectors)
{
    LinAlg::Vector<double, 100000> vectors[1000];

    std::cout << sizeof(vectors) << '\n';
}

TEST_F(VectorTest, initializer_list_constructor)
{
    int* vecPtr = v1.data();
    EXPECT_EQ(vecPtr[0], 1);
    EXPECT_EQ(vecPtr[1], 2);
    EXPECT_EQ(vecPtr[2], 3); 
}

TEST_F(VectorTest, copy_constructor)
{
    EXPECT_EQ(v1, (LinAlg::Vector<int, 3>{ v1 }));
}

TEST_F(VectorTest, smaller_vector_constructor)
{
    EXPECT_EQ((LinAlg::Vector<int, 4>{ v1, 10 }), (LinAlg::Vector<int, 4>{ 1, 2, 3, 10 }));
}

TEST_F(VectorTest, at_function)
{
    EXPECT_EQ(v1.at(0), 1);
    EXPECT_EQ(v1.at(1), 2);
    EXPECT_EQ(v1.at(2), 3);
}

TEST_F(VectorTest, assignment_overload)
{
    LinAlg::Vector<int, 3> assignVec{ 2, 2, 2 };
    assignVec = v1;

    EXPECT_EQ(v1, assignVec);
}

TEST_F(VectorTest, outstream_overload)
{
    testing::internal::CaptureStdout();
    std::cout << v1;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string{"[ 1, 2, 3 ]"});
}

TEST_F(VectorTest, add_overload)
{
   EXPECT_EQ(v1 + v1, (LinAlg::Vector<int, 3>{ 2, 4, 6 })); 
}

TEST_F(VectorTest, add_assign_overload)
{
    v1 += LinAlg::Vector<int, 3>{ 1, 2, 3 };

    EXPECT_EQ(v1, (LinAlg::Vector<int, 3>{ 2, 4, 6 }));
}

TEST_F(VectorTest, add_T_right)
{
    EXPECT_EQ(v1 + 1, (LinAlg::Vector<int, 3>{ 2, 3, 4 }));
}

TEST_F(VectorTest, add_T_left)
{
    EXPECT_EQ(1 + v1, (LinAlg::Vector<int, 3>{ 2, 3, 4 }));
}

TEST_F(VectorTest, add_assign_T)
{
    v1 += 1;

    EXPECT_EQ(v1, (LinAlg::Vector<int, 3>{ 2, 3, 4 }));
}

TEST_F(VectorTest, sub_overload)
{
   EXPECT_EQ(v1 - v1, (LinAlg::Vector<int, 3>{ 0, 0, 0 })); 
}

TEST_F(VectorTest, sub_assign_overload)
{
    v1-= LinAlg::Vector<int, 3>{ 1, 2, 3 };
    EXPECT_EQ(v1, (LinAlg::Vector<int, 3>{ 0, 0, 0 }));
}

TEST_F(VectorTest, sub_T_right)
{
    EXPECT_EQ(v1 - 1, (LinAlg::Vector<int, 3>{ 0, 1, 2 }));
}

TEST_F(VectorTest, sub_T_left)
{
    EXPECT_EQ(1 - v1, (LinAlg::Vector<int, 3>{ 0, -1, -2 }));
}

TEST_F(VectorTest, sub_assign_T)
{
    v1 -= 1;

    EXPECT_EQ(v1, (LinAlg::Vector<int, 3>{ 0, 1, 2 }));
}

TEST_F(VectorTest, unary_sub_overload)
{
    EXPECT_EQ(-v1, (LinAlg::Vector<int, 3>{ -1, -2, -3 }));
}

TEST_F(VectorTest, mult_overload)
{
    EXPECT_EQ(v1 * v1, (LinAlg::Vector<int, 3>{ 1, 4, 9 }));
}

TEST_F(VectorTest, mult_assign_overload)
{
    v1 *= v1;

    EXPECT_EQ(v1, (LinAlg::Vector<int, 3>{ 1, 4, 9 }));
}

TEST_F(VectorTest, mult_T_right)
{
    EXPECT_EQ(v1 * 2, (LinAlg::Vector<int, 3>{ 2, 4, 6 }));
}

TEST_F(VectorTest, mult_T_left)
{
    EXPECT_EQ(2 * v1, (LinAlg::Vector<int, 3>{ 2, 4, 6 }));
}

TEST_F(VectorTest, mult_assign_T)
{
    v1 *= 2;

    EXPECT_EQ(v1, (LinAlg::Vector<int, 3>{ 2, 4, 6 }));
}

TEST_F(VectorTest, div_overload)
{
    EXPECT_EQ(v1 / v1, (LinAlg::Vector<int, 3>{ 1, 1, 1 }));
}

TEST_F(VectorTest, div_assign_overload)
{
    v1 /= v1;

    EXPECT_EQ(v1, (LinAlg::Vector<int, 3>{ 1, 1, 1 }));
}

TEST_F(VectorTest, div_T_right)
{
    EXPECT_EQ((LinAlg::Vector<int, 3>{ 3, 6, 9 }) / 3, v1);
}

TEST_F(VectorTest, div_T_left)
{
    EXPECT_EQ(6 / (LinAlg::Vector<int, 3>{ 6, 3, 2 }), v1);
}

TEST_F(VectorTest, div_assign_T)
{
    LinAlg::Vector<int, 3> v2{ 3, 6, 9 };

    v2 /= 3;

    EXPECT_EQ(v2, v1);
}

TEST_F(VectorTest, dot_product)
{
    ASSERT_FLOAT_EQ(v1.dot(v1), 14.0);
    ASSERT_FLOAT_EQ(v1.dot(LinAlg::Vector<int, 3>{ -3, 0, 1 }), 0.0);
}

TEST_F(VectorTest, length)
{
    ASSERT_FLOAT_EQ((LinAlg::Vector<int, 3>{ 3, 0, 4 }).length(), 5.0);
}

TEST(VECTOR_TEST, angleTo)
{
    LinAlg::Vector<int, 3> vec1{ 1, 0, 0 };
    LinAlg::Vector<int, 3> vec2{ 0, 1, 0 };

    ASSERT_FLOAT_EQ(180*vec1.angleTo(vec1)/M_PI, 0.0);
    ASSERT_FLOAT_EQ(180*vec1.angleTo(vec2)/M_PI, 90.0);
}

TEST(VECTOR_TEST, allClose)
{
    LinAlg::Vector<float, 3> vec1{ 0.1, 0.1, 0.1 };
    LinAlg::Vector<float, 3> vec2{ 1.0, 1.0, 1.0 };

    LinAlg::Vector<float, 3> roundErr{ 0.0, 0.0, 0.0 };

    for(int i = 0; i < 10; ++i){
        roundErr += vec1;
    }

    ASSERT_NE(roundErr, vec2);
    ASSERT_TRUE(vec2.allClose(roundErr));
}

TEST(VECTOR_TEST, normalize)
{
    LinAlg::Vector<float, 3> vec{ 2.3, 5.6, 1.7 };

    vec.normalize();
    ASSERT_FLOAT_EQ(vec.length(), 1.0);
}

TEST(VECTOR_TEST, orthogonal_projection)
{
    LinAlg::Vector<float, 2> a{ 1, 2 };
    LinAlg::Vector<float, 2> b{ 3, 4 };

    LinAlg::Vector<float, 2> proj = orthogonalProject(a, b);
    LinAlg::Vector<float, 2> expected{ 1.32, 1.76 };

    ASSERT_TRUE(proj.allClose(expected));
}

TEST(VECTOR_TEST, cross_product)
{
    LinAlg::Vector<int, 3> u{ 1, 0, 0 };
    LinAlg::Vector<int, 3> v{ 0, 1, 0 };

    LinAlg::Vector<int, 3> expected{ 0, 0, 1 };

    ASSERT_EQ(cross(u, v), expected);
}