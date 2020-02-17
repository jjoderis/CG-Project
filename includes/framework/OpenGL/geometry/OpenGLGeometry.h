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

        bool m_useNormals{ true };
        bool m_useColors{ false };
        bool m_useUVs{ false };

        GLenum m_drawPrimitive{ GL_NONE };

        //if there are faces calculate face and vertex normals and set draw primitive to 
        //correct value (e.g. GL_TRIANGLES for faces with three vertices etc)
        void setUpFaceBasedInformation();

    public:
        OpenGLGeometry();

        OpenGLGeometry(const std::initializer_list<float> &vertexData, const std::initializer_list<int> &faceData);

        OpenGLGeometry(const std::initializer_list<CG::Vector3> &vertices, const std::initializer_list<CG::Face> &faces);

        OpenGLGeometry(const std::vector<CG::Vector3> &vertices, const std::vector<Face> &faces); 

        OpenGLGeometry(const CG::OpenGLGeometry &other);

        CG::OpenGLGeometry& operator= (const CG::OpenGLGeometry &other);

        ~OpenGLGeometry();

        //updates OpenGL Objects to contain all necessary data
        void updateOpenGL();

        void activateNormals();
        void deactivateNormals();
        void activateColors();
        void deactivateColors();
        void activateUVs();
        void deactivateUVs();

        int getVAO() const;
        void setVAO(unsigned int VAO);
        int getVBO() const;
        void setVBO(unsigned int VBO);

        void setDrawPrimitive(GLenum primitive);

        void drawGeometry() const;
    };

}

#endif