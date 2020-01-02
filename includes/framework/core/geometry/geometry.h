#ifndef CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H
#define CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H

#include <vector>
#include <core/face/face.h>
#include <LinAlg/vector/vector.h>
#include <initializer_list>
#include <GL/glew.h>

#define BUFFER_OFFSET(a) ((void*)(a))

namespace CG {

    class Geometry {
    protected:
        std::vector<CG::LinAlg::Vector3<GLfloat>> m_vertices;
        std::vector<Face3> m_faces;

        GLuint m_VAO{ 0 };
        GLuint m_VBO{ 0 };
        void updateOpenGL();

    public:
        Geometry();

        Geometry(const std::initializer_list<float> &vertexData, const std::initializer_list<int> &faceData);

        Geometry(const std::initializer_list<CG::LinAlg::Vector3<float>> &vertices, const std::initializer_list<CG::Face3> &faces);

        Geometry(const std::vector<CG::LinAlg::Vector3<float>> &vertices, const std::vector<Face3> &faces);

        Geometry(const Geometry &other);

        Geometry& operator= (const Geometry &other);

        ~Geometry();

        void setVertices(const std::vector<CG::LinAlg::Vector3<float>> &vertices);

        void setFaces(const std::vector<Face3> &faces);

        std::vector<CG::LinAlg::Vector3<float>>& getVertices();
        int getNumVertices() const;

        std::vector<Face3>& getFaces();
        int getNumFaces() const;

        void bind() const;

        friend bool operator== (const Geometry &g1, const Geometry &g2);
    };

    bool operator== (const Geometry &g1, const Geometry &g2);
}

#endif