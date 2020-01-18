#ifndef CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H
#define CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H

#include <vector>
#include <face/face.h>
#include <color/color.h>
#include <math/math.h>
#include <initializer_list>

namespace CG {
    //A class that handles the vertices and faces of 3D objects; sets up OpenGL Objects that are then used for rendering
    class Geometry {
    protected:
        //points in 3D space that are the base of the geometry
        std::vector<Vector3> m_vertices;
        //normals for all vertices
        std::vector<Vector3> m_vertNormals;
        //optional color data of the given points
        std::vector<RGBA_Color> m_vertColors;
        //faces that define how points are grouped to polygons
        std::vector<Face3> m_faces;
        //normals for all faces
        std::vector<Vector3> m_faceNormals;

        Vector3 m_center{ 0.0, 0.0, 0.0 };

        void calculateFaceNormals();
        void calculateVertexNormals();

    public:
        Geometry();

        //creates vertices and faces from given data and stores them; sets up OpenGL information
        Geometry(const std::initializer_list<float> &vertexData, const std::initializer_list<int> &faceData);

        //stores copies of given vertices and faces; sets up OpenGL information
        Geometry(const std::initializer_list<CG::Vector3> &vertices, const std::initializer_list<CG::Face3> &faces);

        //copies vertices and faces data; sets up OpenGl information
        Geometry(const std::vector<CG::Vector3> &vertices, const std::vector<Face3> &faces);

        //Copy constructor; copies vertices and faces from another geometry; doesn't copy OpenGL information
        Geometry(const Geometry &other);

        //copies vertices and faces from another geometry; doesn't copy OpenGL information
        Geometry& operator= (const Geometry &other);

        ~Geometry();

        //overwrites internal vertex data with copy of given vertex data
        virtual void setVertices(const std::vector<CG::Vector3> &vertices);

        //overwrites internal faces data with copy of given faces data 
        virtual void setFaces(const std::vector<Face3> &faces);
        virtual void clearFaces();

        //sets color for each vertex; given vector has to be of the same size as vertex data vector
        virtual void setVertexColors(const std::vector<CG::RGBA_Color> &colors);
        virtual void clearColors();

        //returns reference to vertices
        std::vector<CG::Vector3>& getVertices();
        std::vector<CG::Vector3>& getVertexNormals();
        int getNumVertices() const;

        //returns reference to faces
        std::vector<Face3>& getFaces();
        std::vector<Vector3>& getFaceNormals();
        int getNumFaces() const;

        friend bool operator== (const Geometry &g1, const Geometry &g2);
    };

    bool operator== (const Geometry &g1, const Geometry &g2);
}

#endif