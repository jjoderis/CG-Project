#ifndef CG_FRAMEWORK_OPENGL_MATERIAL_OPENGLMATERIAL_H
#define CG_FRAMEWORK_OPENGL_MATERIAL_OPENGLMATERIAL_H

#include <GL/glew.h>
#include <OpenGL/shader/shader.h>
#include <core/material/material.h>
#include <vector>

namespace CG{

    typedef struct {
        GLint baseColor;
        GLint modelViewMatrix;
        GLint projectionMatrix;
        GLint normalMatrix;
    } uniformLocations;

    class OpenGLMaterial : public Material{
    protected:
        //name of the stored shaderProgram
        GLuint m_program{ 0 };
        //a collection of shaderInformation that contains all stages of the shaderProgram
        std::vector<CG::ShaderInfo> m_shaders;

    public:
        //the locations of all uniform variables in the shader program
        uniformLocations uniformLocs;

        //creates material with basic shader
        OpenGLMaterial();

        //creates a material with the given vertex and fragment shader
        OpenGLMaterial(const char* vertexShaderData, const char* fragmentShaderData);

        //Copy constructor: copies the color and deep copies the shader information; doesn't copy the program name
        OpenGLMaterial(const OpenGLMaterial &other);

        virtual ~OpenGLMaterial();

        //copies the color and deep copies the shader information; doesn't copy the program name
        OpenGLMaterial& operator= (const OpenGLMaterial &other);

        //sets a new vertex shader and recompiles the program
        void setVertexShader(const char* shaderData);

        //sets a new tesselation shader and recompiles the program
        void setTesselationControlShader(const char* shaderData);
        void setTesselationEvaluationShader(const char* shaderData);

        //sets a new geometry shader and recompiles the program
        void setGeometryShader(const char* shaderData);

        //sets a new fragment shader and recompiles the program
        void setFragmentShader(const char* shaderData);

        //queries locations of uniform variables in the program and stores them
        void getUniformLocs();

        int getProgram() const;

    };

}


#endif