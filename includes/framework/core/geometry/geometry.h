#ifndef CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H
#define CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H

#include <vector>
#include <core/face/face.h>
#include <LinAlg/vector/vector.h>
#include <initializer_list>

namespace CG {

    class Geometry {
    protected:
        std::vector<CG::LinAlg::Vector3<float>> m_vertices;
        std::vector<Face3> m_faces;

    public:
        Geometry(const std::initializer_list<float> &vertexData, const std::initializer_list<int> &faceData);

        Geometry(const std::initializer_list<CG::LinAlg::Vector3<float>> &vertices, const std::initializer_list<CG::Face3> &faces);

        Geometry(const std::vector<CG::LinAlg::Vector3<float>> &vertices, const std::vector<Face3> &faces);

        Geometry(const Geometry &other);

        std::vector<CG::LinAlg::Vector3<float>>& getVertices(){
            return m_vertices;
        }

        std::vector<Face3>& getFaces(){
            return m_faces;
        }

        friend bool operator== (const Geometry &g1, const Geometry &g2);
    };

    bool operator== (const Geometry &g1, const Geometry &g2);
}

#endif