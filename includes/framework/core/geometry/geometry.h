#ifndef CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H
#define CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H

#include <GL/glew.h>
#include <vector>
#include <core/face/face.h>
#include <core/color/color.h>
#include <LinAlg/vector/vector.h>
#include <initializer_list>

#define BUFFER_OFFSET(a) ((void*)(a))

namespace CG {
    //A class that handles the vertices and faces of 3D objects; sets up OpenGL Objects that are then used for rendering
    class Geometry {
    protected:
        //points in 3D space that are the base of the geometry
        std::vector<CG::LinAlg::Vector3<GLfloat>> m_vertices;
        //optional color data of the given points
        std::vector<CG::RGBA_Color> m_vertColors;
        //faces that define how points are grouped to polygons
        std::vector<Face3> m_faces;

        //contains information where and how the relevant data is stored
        GLuint m_VAO{ 0 };
        //contains the vertexData relevant to OpenGL
        GLuint m_VBO{ 0 };
        //contains the faceData relevant to OpenGL
        GLuint m_EBO{ 0 };
        //updates OpenGL Objects to contain all necessary data
        void updateOpenGL();

    public:
        Geometry();

        //creates vertices and faces from given data and stores them; sets up OpenGL information
        Geometry(const std::initializer_list<float> &vertexData, const std::initializer_list<int> &faceData);

        //stores copies of given vertices and faces; sets up OpenGL information
        Geometry(const std::initializer_list<CG::LinAlg::Vector3<float>> &vertices, const std::initializer_list<CG::Face3> &faces);

        //copies vertices and faces data; sets up OpenGl information
        Geometry(const std::vector<CG::LinAlg::Vector3<float>> &vertices, const std::vector<Face3> &faces);

        //Copy constructor; copies vertices and faces from another geometry; doesn't copy OpenGL information
        Geometry(const Geometry &other);

        //copies vertices and faces from another geometry; doesn't copy OpenGL information
        Geometry& operator= (const Geometry &other);

        //deletes OpenGL Objects
        ~Geometry();

        //overwrites internal vertex data with copy of given vertex data
        void setVertices(const std::vector<CG::LinAlg::Vector3<float>> &vertices);

        //overwrites internal faces data with copy of given faces data 
        void setFaces(const std::vector<Face3> &faces);
        void clearFaces();

        //sets color for each vertex; given vector has to be of the same size as vertex data vector
        void setVertexColors(const std::vector<CG::RGBA_Color> &colors);
        void clearColors();

        //returns reference to vertices
        std::vector<CG::LinAlg::Vector3<float>>& getVertices();
        int getNumVertices() const;

        //returns reference to faces
        std::vector<Face3>& getFaces();
        int getNumFaces() const;

        //binds VAO and calls correct draw function based on existance of index data
        void draw() const;

        friend bool operator== (const Geometry &g1, const Geometry &g2);
    };

    bool operator== (const Geometry &g1, const Geometry &g2);
}

#endif