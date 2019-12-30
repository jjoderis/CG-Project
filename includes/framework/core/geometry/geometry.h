#ifndef CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H
#define CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H

#include <core/face/face.h>
#include <LinAlg/vector/vector.h>

namespace CG {

    class Geometry {
    protected:
        Face3* faces = nullptr;
        int numFaces = 0;
        CG::LinAlg::Vector3<float>* vertices = nullptr;
        int numVertices = 0;
    };

}

#endif