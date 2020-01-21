#include <LinAlg/matrix/matrix.h>
#include <iostream>
#include <gtest/gtest.h>

class MatrixTest : public ::testing::Test {
    protected:
        // void SetUp() override {}

        // void TearDown() override {}
        LinAlg::Matrix<int, 2, 2> m1{ { 1, 2 }, { 3, 4 } };
};

TEST(MATRIX_TEST, instantiate_many_matrices)
{
    LinAlg::Matrix<double, 100, 100> matrices[3000];

    std::cout << sizeof(matrices) << '\n';
}

TEST_F(MatrixTest, initializer_list_constructor)
{
    int* matPtr = m1.data();
    EXPECT_EQ(matPtr[0], 1);
    EXPECT_EQ(matPtr[1], 3);
    EXPECT_EQ(matPtr[2], 2);
    EXPECT_EQ(matPtr[3], 4);
}

TEST_F(MatrixTest, at_function)
{
    EXPECT_EQ(m1.at(0, 0), 1);
    EXPECT_EQ(m1.at(0, 1), 2);
    EXPECT_EQ(m1.at(1, 0), 3);
    EXPECT_EQ(m1.at(1, 1), 4);
}

TEST_F(MatrixTest, copy_constructor)
{
    EXPECT_EQ(m1, (LinAlg::Matrix<int, 2, 2>{ m1 }));
}

TEST_F(MatrixTest, assignment_overload)
{
    LinAlg::Matrix<int, 2, 2> matCopy;

    matCopy = m1;
    ASSERT_EQ(m1, matCopy);
}

TEST_F(MatrixTest, outstream_overload)
{
    testing::internal::CaptureStdout();
    std::cout << m1;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string{"[ [ 1, 2 ], [ 3, 4 ] ]"}); 
}

TEST_F(MatrixTest, add_overload)
{
   EXPECT_EQ(m1 + m1, (LinAlg::Matrix<int, 2, 2>{ {2, 4}, {6, 8} })); 
}

TEST_F(MatrixTest, add_assign_overload)
{
    m1 += LinAlg::Matrix<int, 2, 2>{ {1, 2}, {3, 4} };
    EXPECT_EQ(m1, (LinAlg::Matrix<int, 2, 2>{ {2, 4}, {6, 8} }));
}

TEST_F(MatrixTest, add_T_right)
{
    EXPECT_EQ(m1 + 1, (LinAlg::Matrix<int, 2, 2>{ {2, 3}, {4, 5} }));
}

TEST_F(MatrixTest, add_T_left)
{
    EXPECT_EQ(1 + m1, (LinAlg::Matrix<int, 2, 2>{ {2, 3}, {4, 5} }));
}

TEST_F(MatrixTest, add_assign_T)
{
    m1 += 1;

    EXPECT_EQ(m1, (LinAlg::Matrix<int, 2, 2>{ {2, 3}, {4, 5} }));
}

TEST_F(MatrixTest, sub_overload)
{
   EXPECT_EQ(m1 - m1, (LinAlg::Matrix<int, 2, 2>{ {0, 0}, {0, 0} })); 
}

TEST_F(MatrixTest, sub_assign_overload)
{
    m1 -= LinAlg::Matrix<int, 2, 2>{ {1, 2}, {3, 4} };

    EXPECT_EQ(m1, (LinAlg::Matrix<int, 2, 2>{ {0, 0}, {0, 0} }));
}

TEST_F(MatrixTest, sub_T_right)
{
    EXPECT_EQ(m1 - 1, (LinAlg::Matrix<int, 2, 2>{ {0, 1}, {2, 3} }));
}

TEST_F(MatrixTest, sub_T_left)
{
    EXPECT_EQ(1 - m1, (LinAlg::Matrix<int, 2, 2>{ {0, -1}, {-2, -3} }));
}

TEST_F(MatrixTest, sub_assign_T)
{
    m1 -= 1;

    EXPECT_EQ(m1, (LinAlg::Matrix<int, 2, 2>{ {0, 1}, {2, 3} }));
}

TEST_F(MatrixTest, unary_sub_overload)
{
    EXPECT_EQ(-m1, (LinAlg::Matrix<int, 2, 2>{ {-1, -2}, {-3, -4} }));
}

TEST_F(MatrixTest, mult_T_right)
{
    EXPECT_EQ(m1 * 2, (LinAlg::Matrix<int, 2, 2>{ {2, 4}, {6, 8} }));
}

TEST_F(MatrixTest, mult_T_left)
{
    EXPECT_EQ(2 * m1, (LinAlg::Matrix<int, 2, 2>{ {2, 4}, {6, 8} }));
}

TEST_F(MatrixTest, mult_assign_T)
{
    m1 *= 2;

    EXPECT_EQ(m1, (LinAlg::Matrix<int, 2, 2>{ {2, 4}, {6, 8} }));
}

TEST_F(MatrixTest, div_overload)
{
    EXPECT_EQ(m1 / m1, (LinAlg::Matrix<int, 2, 2>{ {1, 1}, {1, 1} }));
}

TEST_F(MatrixTest, div_assign_overload)
{
    m1 /= m1;

    EXPECT_EQ(m1, (LinAlg::Matrix<int, 2, 2>{ {1, 1}, {1, 1} }));
}

TEST_F(MatrixTest, div_T_right)
{
    EXPECT_EQ((LinAlg::Matrix<int, 2, 2>{ {3, 6}, {9, 12} }) / 3, m1);
}

TEST_F(MatrixTest, div_T_left)
{
    EXPECT_EQ(12 / m1, (LinAlg::Matrix<int, 2, 2>{ {12, 6}, {4, 3} }));
}

TEST_F(MatrixTest, div_assign_T)
{
    LinAlg::Matrix<int, 2, 2> doubleM{ {2, 4}, {6, 8} };

    doubleM /= 2;

    EXPECT_EQ(doubleM, m1);
}

TEST_F(MatrixTest, set_identity)
{
    m1.setIdentity();

    EXPECT_EQ(m1, (LinAlg::Matrix<int, 2, 2>{ {1, 0}, {0, 1} }));
}

TEST(MATRIX_TEST, transpose_a_b)
{
    LinAlg::Matrix<int, 3, 2> mat{ {1, 2}, {3, 4}, {5, 6} };

    LinAlg::Matrix<int, 2, 3> trans{ {1, 3, 5}, {2, 4, 6} };

    EXPECT_EQ(transpose(mat), trans);
}

TEST(MATRIX_TEST, transpose_a_a)
{
    LinAlg::Matrix<int, 2, 2> mat{ {1, 2}, {3, 4} };

    LinAlg::Matrix<int, 2, 2> trans{ {1, 3}, {2, 4} };

    EXPECT_EQ(transpose(mat), trans);
}

TEST_F(MatrixTest, transpose_member_function)
{
    m1.transpose();

    EXPECT_EQ(m1, (LinAlg::Matrix<int, 2, 2>{ {1, 3}, {2, 4} }));
}

TEST_F(MatrixTest, trace_member_function)
{
    EXPECT_DOUBLE_EQ(m1.trace(), 5);
}

TEST_F(MatrixTest, matrix_matrix_multiplication)
{
    EXPECT_EQ(m1 * m1, (LinAlg::Matrix<int, 2, 2>{ {7, 10}, {15, 22} }));
}

TEST(MATRIX_TEST, matrix_vector_multiplication)
{
    LinAlg::Matrix<int, 3, 2> mat{ {1, 2}, {3, 4}, {5, 6} };
    LinAlg::Vector<int, 2> vec{1, 2};

    LinAlg::Vector<int, 3> res{5, 11, 17};

    EXPECT_EQ(mat * vec, res);
}

TEST_F(MatrixTest, mult_assign_overload)
{
    m1 *= m1;

    EXPECT_EQ(m1, (LinAlg::Matrix<int, 2, 2>{ {7, 10}, {15, 22} }));
}