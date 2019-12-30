#include <iostream>
#include <gtest/gtest.h>
#include "../face.h"

TEST(FACE_TEST, test_constructor)
{
    CG::Face3 face{1, 2, 3};

    EXPECT_EQ(face.a, 1);
    EXPECT_EQ(face.b, 2);
    EXPECT_EQ(face.c, 3);
}

TEST(FACE_TEST, copy_constructor)
{
    CG::Face3 face{1, 2, 3};
    CG::Face3 faceCopy{ face };

    EXPECT_EQ(faceCopy.a, 1);
    EXPECT_EQ(faceCopy.b, 2);
    EXPECT_EQ(faceCopy.c, 3);
}

TEST(FACE_TEST, assignment_overload)
{
    CG::Face3 face{1, 2, 3};
    CG::Face3 faceCopy{1, 1, 1};

    faceCopy = face;

    EXPECT_EQ(faceCopy.a, 1);
    EXPECT_EQ(faceCopy.b, 2);
    EXPECT_EQ(faceCopy.c, 3);
}

TEST(FACE_TEST, outstream_overload)
{
    CG::Face3 face{1, 2, 3};

    testing::internal::CaptureStdout();
    std::cout << face;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, std::string{"[ a: 1, b: 2, c: 3 ]"}); 
}