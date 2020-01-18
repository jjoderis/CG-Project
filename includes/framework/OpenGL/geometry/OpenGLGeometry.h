#ifndef CG_FRAMEWORK_OPENGL_OPENGLGEOMETRY_OPENGLGEOMETRY_H
#define CG_FRAMEWORK_OPENGL_OPENGLGEOMETRY_OPENGLGEOMETRY_H

#include <GL/glew.h>
#include <color/color.h>
#include <geometry/geometry.h>

#define BUFFER_OFFSET(a) ((void*)(a))

namespace CG{

    class OpenGLGeometry : virtual public Geometry{
    protected:
        //contains information where and how the relevant data is stored
        unsigned int m_VAO{ 0 };
        //contains the vertexData relevant to OpenGL
        unsigned int m_VBO{ 0 };
        //contains the faceData relevant to OpenGL
        unsigned int m_EBO{ 0 };
        //updates OpenGL Objects to contain all necessary data
        void updateOpenGL();

    public:
        OpenGLGeometry();

        OpenGLGeometry(const std::initializer_list<float> &vertexData, const std::initializer_list<int> &faceData);

        OpenGLGeometry(const std::initializer_list<CG::Vector3> &vertices, const std::initializer_list<CG::Face3> &faces);

        OpenGLGeometry(const std::vector<CG::Vector3> &vertices, const std::vector<Face3> &faces); 

        OpenGLGeometry(const CG::OpenGLGeometry &other);

        CG::OpenGLGeometry& operator= (const CG::OpenGLGeometry &other);

        ~OpenGLGeometry();

        virtual void setVertices(const std::vector<CG::Vector3> &vertices);

        virtual void setFaces(const std::vector<Face3> &faces);
        virtual void clearFaces();

        virtual void setVertexColors(const std::vector<CG::RGBA_Color> &colors);
        virtual void clearColors();


        int getVAO() const;
        int getVBO() const;
    };

}

#endif