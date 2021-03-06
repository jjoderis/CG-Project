#ifndef CG_FRAMEWORK_OPENGL_MATERIAL_OPENGLMATERIAL_H
#define CG_FRAMEWORK_OPENGL_MATERIAL_OPENGLMATERIAL_H

#include <GL/glew.h>
#include <color/color.h>
#include <OpenGL/shader/shader.h>
#include <material/material.h>
#include <initializer_list>
#include <map>
#include <memory>
#include <OpenGL/texture/OpenGLTexture.h>

namespace CG{

    class OpenGLMaterial : public Material{
    protected:
        //name of the stored shaderProgram
        GLuint m_program{ 0 };
        //a collection of shaderInformation that contains all stages of the shaderProgram
        std::vector<CG::ShaderInfo> m_shaders;

        //all texture object bound used by this object
        std::vector<std::shared_ptr<CG::OpenGLTexture>> m_textures;

        //the locations of all uniform variables in the shader program
        mutable std::map<std::string, GLint> m_uniforms;

    public:
        //creates material with basic shader
        OpenGLMaterial();

        OpenGLMaterial(const CG::RGBA_Color &color);

        //creates a material with the given vertex and fragment shader
        OpenGLMaterial(const std::initializer_list<CG::ShaderInfo> &shaderData);

        //Copy constructor: copies the color and deep copies the shader information; doesn't copy the program name
        OpenGLMaterial(const OpenGLMaterial &other);

        virtual ~OpenGLMaterial();

        //copies the color and deep copies the shader information; doesn't copy the program name
        OpenGLMaterial& operator= (const OpenGLMaterial &other);

        //sets a new vertex shader and recompiles the program
        void setVertexShader(const std::string shaderData, bool isFile);

        //sets a new tesselation shader and recompiles the program
        void setTesselationControlShader(const std::string shaderData, bool isFile);
        void setTesselationEvaluationShader(const std::string shaderData, bool isFile);

        //sets a new geometry shader and recompiles the program
        void setGeometryShader(const std::string shaderData, bool isFile);

        //sets a new fragment shader and recompiles the program
        void setFragmentShader(const std::string shaderData, bool isFile);

        //queries location of uniform variable in the program and stores it
        GLint getUniform(const char* name) const;
        GLint getUniform(const std::string &name) const;

        int getProgram() const;

        
        std::vector<std::shared_ptr<CG::OpenGLTexture>>& getTextures();
        
        int getNumTextures() const;

        void setupUniformData() const;

        void addTexture(std::shared_ptr<CG::OpenGLTexture> texture);

        void bindTextures() const;

        void unbindTextures() const;
    };

}


#endif