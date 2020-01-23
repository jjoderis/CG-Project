#include <iostream>
#include <gtest/gtest.h>
#include "../geometry.h"
#include <vector>

class GeometryTest : public ::testing::Test {
    protected:
        std::vector<CG::Vector3> triangle{
            {  0.0,  0.0,  0.0 },
            {  1.0,  0.0,  0.0 },
            {  0.0,  1.0,  0.0 },
            {  0.0,  0.0,  0.0 },
            {  1.0,  0.0,  0.0 },
            {  0.0,  0.0, -1.0 },
            {  0.0,  0.0,  0.0 },
            {  0.0,  1.0,  0.0 },
            {  0.0,  0.0,  1.0 }
        };

        std::vector<CG::Face> triangleFace{
            { 0, 1, 2 },
            { 3, 4, 5 },
            { 6, 7, 8 }
        };

        CG::Geometry trianglesGeo{
            {
                {  0.0,  0.0,  0.0 },
                {  1.0,  0.0,  0.0 },
                {  0.0,  1.0,  0.0 },
                {  0.0,  0.0,  0.0 },
                {  1.0,  0.0,  0.0 },
                {  0.0,  0.0, -1.0 },
                {  0.0,  0.0,  0.0 },
                {  0.0,  1.0,  0.0 },
                {  0.0,  0.0,  1.0 }
            },
            {
                { 0, 1, 2 },
                { 3, 4, 5 },
                { 6, 7, 8 }
            }
        };
};

TEST_F(GeometryTest, vertex_face_list_constructor){
    EXPECT_EQ(trianglesGeo.getVertices(), triangle);
    EXPECT_EQ(trianglesGeo.getFaces(), triangleFace);
}

TEST_F(GeometryTest, vertex_face_vector_constructor){
    CG::Geometry vectorGeometry{ triangle, triangleFace };

    EXPECT_EQ(vectorGeometry, trianglesGeo);
}

TEST_F(GeometryTest, copy_constructor){
    CG::Geometry copyGeo{ trianglesGeo };

    EXPECT_EQ(copyGeo, trianglesGeo);
}

TEST_F(GeometryTest, assignment_overload){
    CG::Geometry assignGeo{};

    assignGeo = trianglesGeo;

    EXPECT_EQ(assignGeo, trianglesGeo);
}

TEST_F(GeometryTest, calculateFaceNormals){
    EXPECT_TRUE(trianglesGeo.getFaceNormals()[0].allClose(CG::Vector3{ 0.0, 0.0, 1.0 }));
    EXPECT_TRUE(trianglesGeo.getFaceNormals()[1].allClose(CG::Vector3{ 0.0, 1.0, 0.0 }));
    EXPECT_TRUE(trianglesGeo.getFaceNormals()[2].allClose(CG::Vector3{ 1.0, 0.0, 0.0 }));
}

TEST_F(GeometryTest, calculateVertexNormals){
    EXPECT_TRUE(trianglesGeo.getVertexNormals()[0].allClose(CG::Vector3{ 0.0, 0.0, 1.0 }));
    EXPECT_TRUE(trianglesGeo.getVertexNormals()[1].allClose(CG::Vector3{ 0.0, 0.0, 1.0 }));
    EXPECT_TRUE(trianglesGeo.getVertexNormals()[2].allClose(CG::Vector3{ 0.0, 0.0, 1.0 }));
    EXPECT_TRUE(trianglesGeo.getVertexNormals()[3].allClose(CG::Vector3{ 0.0, 1.0, 0.0 }));
    EXPECT_TRUE(trianglesGeo.getVertexNormals()[4].allClose(CG::Vector3{ 0.0, 1.0, 0.0 }));
    EXPECT_TRUE(trianglesGeo.getVertexNormals()[5].allClose(CG::Vector3{ 0.0, 1.0, 0.0 }));
    EXPECT_TRUE(trianglesGeo.getVertexNormals()[6].allClose(CG::Vector3{ 1.0, 0.0, 0.0 }));
    EXPECT_TRUE(trianglesGeo.getVertexNormals()[7].allClose(CG::Vector3{ 1.0, 0.0, 0.0 }));
    EXPECT_TRUE(trianglesGeo.getVertexNormals()[8].allClose(CG::Vector3{ 1.0, 0.0, 0.0 }));
}