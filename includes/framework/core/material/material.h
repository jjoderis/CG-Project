#ifndef CG_FRAMEWORK_CORE_MATERIAL_MATERIAL_H
#define CG_FRAMEWORK_CORE_MATERIAL_MATERIAL_H

#include <GL/glew.h>
#include <core/color/color.h>
#include <core/shader/shader.h>
#include <vector>

namespace CG{
    typedef struct {
        GLint baseColor;
        GLint modelViewMatrix;
        GLint projectionMatrix;
        GLint normalMatrix;
    } uniformLocations;

    //A class that handles OpenGL shader information
    class Material{
    protected:
        //name of the stored shaderProgram
        GLuint m_program;
        //a base color
        CG::RGBA_Color m_color{ 1.0, 1.0, 1.0, 1.0 };
        //a collection of shaderInformation that contains all stages of the shaderProgram
        std::vector<CG::ShaderInfo> m_shaders;

    public:
        //the locations of all uniform variables in the shader program
        uniformLocations uniformLocs;

        //creates a material with a basic shader that only renders triangles with the stored color
        Material();

        //creates a Material and sets a color
        Material(RGBA_Color color);

        //creates a Material and sets a color
        Material(RGB_Color color);

        //creates a material with the given vertex and fragment shader
        Material(const char* vertexShaderData, const char* fragmentShaderData);

        //Copy constructor: copies the color and deep copies the shader information; doesn't copy the program name
        Material(const Material &other);

        //copies the color and deep copies the shader information; doesn't copy the program name
        Material& operator= (const Material &other);

        //delete all shaders and the program of the program
        ~Material();

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

        //sets new color
        void setColor(RGB_Color color);
        void setColor(GLfloat r, GLfloat g, GLfloat b);
        void setColor(RGBA_Color color);
        void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
        RGBA_Color& getColor();
    };
}

#endif