#include <iostream>
#include <gtest/gtest.h>
#include "../geometry.h"
#include <vector>

TEST(GEOMETRY_TEST, test_fundamental_init_list_constructor){
    CG::Geometry geometry{
        {
         1.0, 1.0, 1.0,
         1.0, 1.0, 1.0,
         1.0, 1.0, 1.0   
        },
        { 0, 1, 2 }
    };

    CG::LinAlg::Vector3<float> vec{1.0, 1.0, 1.0};
    CG::Face3 face{ 0, 1, 2 };

    std::vector<CG::LinAlg::Vector3<float>> vertices = geometry.getVertices();
    EXPECT_EQ(vertices[0], vec);
    EXPECT_EQ(vertices[1], vec);
    EXPECT_EQ(vertices[2], vec);
    EXPECT_EQ(geometry.getFaces()[0], face);
}

TEST(GEOMETRY_TEST, test_init_list_constructor){
    CG::Geometry geometry1{
        {
         1.0, 1.0, 1.0,
         1.0, 1.0, 1.0,
         1.0, 1.0, 1.0   
        },
        { 0, 1, 2 }
    };

    CG::Geometry geometry2{
        {
            CG::LinAlg::Vector3<float>{ 1.0, 1.0, 1.0},
            CG::LinAlg::Vector3<float>{ 1.0, 1.0, 1.0},
            CG::LinAlg::Vector3<float>{ 1.0, 1.0, 1.0},
        },
        {
            CG::Face3{ 0, 1, 2 }
        }
    };

    EXPECT_EQ(geometry1, geometry2);
}

TEST(GEOMETRY_TEST, test_std_vector_constructor){
    CG::Geometry geometry1{
        {
         1.0, 1.0, 1.0,
         1.0, 1.0, 1.0,
         1.0, 1.0, 1.0   
        },
        { 0, 1, 2 }
    };

    std::vector<CG::LinAlg::Vector3<float>> vertices{
        CG::LinAlg::Vector3<float>{ 1.0, 1.0, 1.0},
        CG::LinAlg::Vector3<float>{ 1.0, 1.0, 1.0},
        CG::LinAlg::Vector3<float>{ 1.0, 1.0, 1.0},
    };

    std::vector<CG::Face3> faces{ CG::Face3{ 0, 1, 2 } };

    CG::Geometry geometry2{vertices, faces};

    EXPECT_EQ(geometry1, geometry2);
}

TEST(GEOMETRY_TEST, test_copy_constructor){
    std::vector<CG::LinAlg::Vector3<float>> vertices{
        CG::LinAlg::Vector3<float>{ 1.0, 1.0, 1.0},
        CG::LinAlg::Vector3<float>{ 1.0, 1.0, 1.0},
        CG::LinAlg::Vector3<float>{ 1.0, 1.0, 1.0},
    };

    std::vector<CG::Face3> faces{ CG::Face3{ 0, 1, 2 } };

    CG::Geometry geometry{vertices, faces};
    CG::Geometry copy{ geometry };

    EXPECT_EQ(geometry, copy);
}