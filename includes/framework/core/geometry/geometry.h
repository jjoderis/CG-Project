#ifndef CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H
#define CG_FRAMEWORK_CORE_GEOMETRY_GEOMETRY_H

#include <vector>
#include <face/face.h>
#include <color/color.h>
#include <math/math.h>
#include <initializer_list>

namespace CG {

    //type of mapping that can be used by a geoemtry
    enum TextureMapping{ SPHERE_MAPPING, BOX_MAPPING };

    //A class that handles the vertices and faces of 3D objects
    class Geometry {
    protected:
        //points in 3D space that are the base of the geometry
        std::vector<Vector3> m_vertices;
        //normals for all vertices
        std::vector<Vector3> m_vertNormals;
        //optional color data of the given points
        std::vector<RGBA_Color> m_vertColors;
        //faces that define how points are grouped to polygons
        std::vector<Face> m_faces;
        //normals for all faces
        std::vector<Vector3> m_faceNormals;
        // uv values used for texture mapping
        std::vector<Vector2> m_vertUVs;

        Vector3 m_center{ 0.0, 0.0, 0.0 };

        TextureMapping m_mapType{ SPHERE_MAPPING };

    public:
        Geometry();

        //stores copies of given vertices and faces
        Geometry(const std::initializer_list<CG::Vector3> &vertices, const std::initializer_list<CG::Face> &faces);

        //copies vertices and faces data
        Geometry(const std::vector<CG::Vector3> &vertices, const std::vector<Face> &faces);

        //Copy constructor; copies vertices and faces from another geometry
        Geometry(const Geometry &other);

        //copies vertices and faces from another geometry
        Geometry& operator= (const Geometry &other);

        ~Geometry();

        void calculateFaceNormals();
        void calculateVertexNormals();

        void calculateVertexUVs();
        void calculateSphereMapping();
        void calculateBoxMapping();

        //overwrites internal vertex data with copy of given vertex data
        virtual void setVertices(const std::vector<CG::Vector3> &vertices);

        //overwrites internal faces data with copy of given faces data 
        virtual void setFaces(const std::vector<Face> &faces);
        virtual void clearFaces();

        //sets color for each vertex; given vector has to be of the same size as vertex data vector
        virtual void setVertexColors(const std::vector<CG::RGBA_Color> &colors);
        virtual void clearColors();

        void setVertexNormals(const std::vector<CG::Vector3> &vNormals);

        void setFaceNormals(const std::vector<CG::Vector3> &fNormals);

        //returns reference to vertices
        std::vector<CG::Vector3>& getVertices();
        std::vector<CG::Vector3>& getVertexNormals();
        int getNumVertices() const;

        //returns reference to faces
        std::vector<Face>& getFaces();
        std::vector<Vector3>& getFaceNormals();
        int getNumFaces() const;

        //returns reference to the UV values of all vertices
        std::vector<Vector2>& getVertUVs();

        void setMapType(TextureMapping mapType);

        friend bool operator== (const Geometry &g1, const Geometry &g2);
    };

    bool operator== (const Geometry &g1, const Geometry &g2);
}

#endif