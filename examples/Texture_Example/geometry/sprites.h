#ifndef CG_EXAMPLES_TEXTURE_GEOMETRY_SPRTITES_H
#define CG_EXAMPLES_TEXTURE_GEOMETRY_SPRTITES_H

#include <OpenGL/geometry/OpenGLGeometry.h>
#include <random>
#include <memory>

CG::OpenGLGeometry setUpSnowFlakes(){

    int numPoints = 1000;

    std::vector<CG::Vector3> points;
    points.resize(numPoints);

    for(int i = 0; i < numPoints; ++i){
        float randX{static_cast<float>(rand())/(RAND_MAX/20) - 10.0f};
        float randY{static_cast<float>(rand())/(RAND_MAX/20) - 10.0f};
        float randZ{static_cast<float>(rand())/(RAND_MAX/20) - 10.0f};
        points[i] = CG::Vector3{ randX, randY, randZ };
    }

    CG::OpenGLGeometry pointGeo{};

    pointGeo.setVertices(points);

    return pointGeo;
}

#endif