#include "boxGeometry.h"

CG::BoxGeometry::BoxGeometry(float width, float height, float depth) 
    : m_bottomLeft{ -width/2, -height/2, depth/2 }, m_topRight{ width/2, height/2, -depth/2 }
{
    m_vertices = {
        {-width/2, -height/2,  depth/2}, //0: fbl
        { width/2, -height/2,  depth/2}, //1: fbr
        { width/2,  height/2,  depth/2}, //2: ftr
        {-width/2,  height/2,  depth/2}, //3: ftl
        {-width/2, -height/2, -depth/2}, //4: bbl
        { width/2, -height/2, -depth/2}, //5: bbr
        { width/2,  height/2, -depth/2}, //6: btr
        {-width/2,  height/2, -depth/2}  //7: btl
    };

    m_faces = {
        { 0, 1, 3 }, //front
        { 1, 2, 3 }, //front
        { 1, 5, 2 }, //right
        { 5, 6, 2 }, //right
        { 5, 4, 6 }, //back
        { 4, 7, 6 }, //back
        { 4, 0, 3 }, //left
        { 0, 3, 7 }, //left
        { 3, 2, 7 }, //top
        { 2, 6, 7 }, //top
        { 4, 5, 0 }, //bottom
        { 5, 1, 0 }
    };

    calculateVertexNormals();
}

CG::BoxGeometry::BoxGeometry() : BoxGeometry(1.0, 1.0, 1.0) {}

float CG::BoxGeometry::getWidth(){
    return m_topRight.at(0) - m_bottomLeft.at(0); 
}
float CG::BoxGeometry::getHeigth(){
    return m_topRight.at(1) - m_bottomLeft.at(1);
}
float CG::BoxGeometry::getDepth(){
    return m_bottomLeft.at(2) - m_topRight.at(1);
}