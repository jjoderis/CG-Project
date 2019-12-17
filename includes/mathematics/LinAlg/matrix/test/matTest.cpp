#include <LinAlg/matrix/matrix.h>
#include <iostream>
#include <gtest/gtest.h>


TEST(MATRIX_TEST, instantiate_many_matrices)
{
    CG::LinAlg::Matrix<double, 100, 100> matrices[3000];

    std::cout << sizeof(matrices) << '\n';
}

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

TEST(MATRIX_TEST, sub_overload)
{
   CG::LinAlg::Matrix<int, 2, 2> mat1{ {1, 2}, {3, 4} };
   CG::LinAlg::Matrix<int, 2, 2> mat2{ {1, 2}, {3, 4} };

   CG::LinAlg::Matrix<int, 2, 2> diff{ {0, 0}, {0, 0} };
   EXPECT_EQ(mat1 - mat2, diff); 
}

TEST(MATRIX_TEST, sub_assign_overload)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {1, 2}, {3, 4} };
    mat -= CG::LinAlg::Matrix<int, 2, 2>{ {1, 2}, {3, 4} };

    CG::LinAlg::Matrix<int, 2, 2> diff{ {0, 0}, {0, 0} };
    EXPECT_EQ(mat, diff);
}

TEST(MATRIX_TEST, sub_T_right)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {1, 1}, {1, 1} };

    CG::LinAlg::Matrix<int, 2, 2> zeros{ {0, 0}, {0, 0} };

    EXPECT_EQ(mat - 1, zeros);
}

TEST(MATRIX_TEST, sub_T_left)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {1, 1}, {1, 1} };

    CG::LinAlg::Matrix<int, 2, 2> zeros{ {0, 0}, {0, 0} };

    EXPECT_EQ(1 - mat, zeros);
}

TEST(MATRIX_TEST, sub_assign_T)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {1, 1}, {1, 1} };

    CG::LinAlg::Matrix<int, 2, 2> zeros{ {0, 0}, {0, 0} };

    mat -= 1;

    EXPECT_EQ(mat, zeros);
}

TEST(MATRIX_TEST, unary_sub_overload)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ { 1, -10}, { 2, -8} };

    CG::LinAlg::Matrix<int, 2, 2> inv{ {-1,  10}, {-2,  8} };

    EXPECT_EQ(-mat, inv);
}


TEST(MATRIX_TEST, mult_overload)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {2, 3}, {4, 5} };

    CG::LinAlg::Matrix<int, 2, 2> square{ {4, 9}, {16, 25} };

    EXPECT_EQ(mat * mat, square);
}

TEST(MATRIX_TEST, mult_assign_overload)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {2, 3}, {4, 5} };

    CG::LinAlg::Matrix<int, 2, 2> square{ {4, 9}, {16, 25} };

    mat *= mat;

    EXPECT_EQ(mat, square);
}

TEST(MATRIX_TEST, mult_T_right)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {1, 1}, {1, 1} };

    CG::LinAlg::Matrix<int, 2, 2> twos{ {2, 2}, {2, 2} };

    EXPECT_EQ(mat * 2, twos);
}

TEST(MATRIX_TEST, mult_T_left)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {1, 1}, {1, 1} };

    CG::LinAlg::Matrix<int, 2, 2> twos{ {2, 2}, {2, 2} };

    EXPECT_EQ(2 * mat, twos);
}

TEST(MATRIX_TEST, mult_assign_T)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {1, 1}, {1, 1} };

    CG::LinAlg::Matrix<int, 2, 2> twos{ {2, 2}, {2, 2} };

    mat *= 2;

    EXPECT_EQ(mat, twos);
}

TEST(MATRIX_TEST, div_overload)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {4, 9}, {3, 5} };

    CG::LinAlg::Matrix<int, 2, 2> ones{ {1, 1}, {1, 1} };

    EXPECT_EQ(mat / mat, ones);
}

TEST(MATRIX_TEST, div_assign_overload)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {2, 3}, {4, 7} };

    CG::LinAlg::Matrix<int, 2, 2> ones{ {1, 1}, {1, 1} };

    mat /= mat;

    EXPECT_EQ(mat, ones);
}

TEST(MATRIX_TEST, div_T_right)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {3, 9}, {6, 12} };

    CG::LinAlg::Matrix<int, 2, 2> quot{ {1, 3}, {2, 4} };

    EXPECT_EQ(mat / 3, quot);
}

TEST(MATRIX_TEST, div_T_left)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {2, 4}, {8, 16} };

    CG::LinAlg::Matrix<int, 2, 2> quot{ {8, 4}, {2, 1} };

    EXPECT_EQ(16 / mat, quot);
}

TEST(MATRIX_TEST, div_assign_T)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {10, 20}, {5, 15} };

    CG::LinAlg::Matrix<int, 2, 2> quot{ {2, 4}, {1, 3} };

    mat /= 5;

    EXPECT_EQ(mat, quot);
}

TEST(MATRIX_TEST, set_identity)
{
    CG::LinAlg::Matrix<int, 3, 3> mat;

    CG::LinAlg::Matrix<int, 3, 3> identity{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };

    mat.setIdentity();

    EXPECT_EQ(mat, identity);
}

TEST(MATRIX_TEST, transpose_a_b)
{
    CG::LinAlg::Matrix<int, 3, 2> mat{ {1, 2}, {3, 4}, {5, 6} };

    CG::LinAlg::Matrix<int, 2, 3> trans{ {1, 3, 5}, {2, 4, 6} };

    EXPECT_EQ(transpose(mat), trans);
}

TEST(MATRIX_TEST, transpose_a_a)
{
    CG::LinAlg::Matrix<int, 2, 2> mat{ {1, 2}, {3, 4} };

    CG::LinAlg::Matrix<int, 2, 2> trans{ {1, 3}, {2, 4} };

    EXPECT_EQ(transpose(mat), trans);
}

TEST(MATRIX_TEST, transpose_member_function)
{
    CG::LinAlg::Matrix<int, 3, 3> mat{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    CG::LinAlg::Matrix<int, 3, 3> trans{ {1, 4, 7}, {2, 5, 8}, {3, 6, 9} };

    mat.transpose();

    EXPECT_EQ(mat, trans);
}

TEST(MATRIX_TEST, trace_member_function)
{
    CG::LinAlg::Matrix<int, 3, 3> mat{ {2, 3, 4}, {5, 6, 7}, {8, 9, 10} };

    EXPECT_DOUBLE_EQ(mat.trace(), 18);
}

TEST(MATRIX_TEST, matrix_matrix_multiplication)
{
    CG::LinAlg::Matrix<int, 3, 2> mat1{ {1, 2}, {3, 4}, {5, 6} };
    CG::LinAlg::Matrix<int, 2, 4> mat2{ {1, 2, 3, 4}, {5, 6, 7, 8} };

    CG::LinAlg::Matrix<int, 3, 4> res{ {11, 14, 17, 20}, {23, 30, 37, 44}, {35, 46, 57, 68} };

    EXPECT_EQ(dot(mat1, mat2), res);
}

TEST(MATRIX_TEST, matrix_vector_multiplication)
{
    CG::LinAlg::Matrix<int, 3, 2> mat{ {1, 2}, {3, 4}, {5, 6} };
    CG::LinAlg::Vector<int, 2> vec{1, 2};

    CG::LinAlg::Vector<int, 3> res{5, 11, 17};

    EXPECT_EQ(dot(mat, vec), res);
}