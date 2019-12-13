#include "../matrix.h"
#include <iostream>
#include <gtest/gtest.h>

TEST(MATRIX_TEST, initializer_list_constructor)
{
    CG::LinAlg::Matrix<float, 2, 2> mat{ {1.0, 2.0}, {3.0, 4.0} };

    float* matPtr = mat;
    EXPECT_EQ(matPtr[0], 1.0);
    EXPECT_EQ(matPtr[1], 3.0);
    EXPECT_EQ(matPtr[2], 2.0);
    EXPECT_EQ(matPtr[3], 4.0);
}

TEST(MATRIX_TEST, at_function)
{
    CG::LinAlg::Matrix<float, 3, 3> mat{ {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };

    EXPECT_EQ(mat.at(0, 0), 1.0);
    EXPECT_EQ(mat.at(0, 1), 2.0);
    EXPECT_EQ(mat.at(0, 2), 3.0);
    EXPECT_EQ(mat.at(1, 0), 4.0);
    EXPECT_EQ(mat.at(1, 1), 5.0);
    EXPECT_EQ(mat.at(1, 2), 6.0);
    EXPECT_EQ(mat.at(2, 0), 7.0);
    EXPECT_EQ(mat.at(2, 1), 8.0);
    EXPECT_EQ(mat.at(2, 2), 9.0);
}

TEST(MATRIX_TEST, copy_constructor)
{
    CG::LinAlg::Matrix<float, 2, 2> mat{ {1.0, 2.0}, {3.0, 4.0} };
    CG::LinAlg::Matrix<float, 2, 2> matCopy{ mat };

    EXPECT_EQ(mat, matCopy);
}

TEST(MATRIX_TEST, assignment_overload)
{
    CG::LinAlg::Matrix<float, 2, 2> mat{ {1.0, 2.0}, {3.0, 4.0} };

    CG::LinAlg::Matrix<float, 2, 2> matCopy;

    matCopy = mat;
    ASSERT_EQ(mat, matCopy);
}

TEST(MATRIX_TEST, outstream_overload)
{
    CG::LinAlg::Matrix<float, 2, 2> mat{ {1.0, 2.0}, {3.0, 4.0} };

    testing::internal::CaptureStdout();
    std::cout << mat;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string{"[ [ 1, 2 ], [ 3, 4 ] ]"}); 
}

TEST(MATRIX_TEST, add_overload)
{
   CG::LinAlg::Matrix<float, 2, 2> mat1{ {1.0, 2.0}, {3.0, 4.0} };
   CG::LinAlg::Matrix<float, 2, 2> mat2{ {1.0, 2.0}, {3.0, 4.0} };

   CG::LinAlg::Matrix<float, 2, 2> sum{ {2.0, 4.0}, {6.0, 8.0} };
   EXPECT_EQ(mat1 + mat2, sum); 
}

TEST(MATRIX_TEST, add_assign_overload)
{
    CG::LinAlg::Matrix<float, 2, 2> mat{ {1.0, 2.0}, {3.0, 4.0} };
    mat += CG::LinAlg::Matrix<float, 2, 2>{ {1.0, 2.0}, {3.0, 4.0} };

    CG::LinAlg::Matrix<float, 2, 2> sum{ {2.0, 4.0}, {6.0, 8.0} };
    EXPECT_EQ(mat, sum);
}

TEST(MATRIX_TEST, add_T_right)
{
    CG::LinAlg::Matrix<float, 2, 2> mat{ {0.0, 0.0}, {0.0, 0.0} };

    CG::LinAlg::Matrix<float, 2, 2> ones{ {1.0, 1.0}, {1.0, 1.0} };

    EXPECT_EQ(mat + 1.0f, ones);
}

TEST(MATRIX_TEST, add_T_left)
{
    CG::LinAlg::Matrix<float, 2, 2> mat{ {0.0, 0.0}, {0.0, 0.0} };

    CG::LinAlg::Matrix<float, 2, 2> ones{ {1.0, 1.0}, {1.0, 1.0} };

    EXPECT_EQ(1.0f + mat, ones);
}

TEST(MATRIX_TEST, add_assign_T)
{
    CG::LinAlg::Matrix<float, 2, 2> mat{ {0.0, 0.0}, {0.0, 0.0} };

    CG::LinAlg::Matrix<float, 2, 2> ones{ {1.0, 1.0}, {1.0, 1.0} };

    mat += 1;

    EXPECT_EQ(mat, ones);
}