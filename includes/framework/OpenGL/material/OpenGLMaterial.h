#ifndef CG_FRAMEWORK_OPENGL_MATERIAL_OPENGLMATERIAL_H
#define CG_FRAMEWORK_OPENGL_MATERIAL_OPENGLMATERIAL_H

#include <GL/glew.h>
#include <color/color.h>
#include <OpenGL/shader/shader.h>
#include <material/material.h>
#include <initializer_list>
#include <map>
#include <stb_image.h>
#include <memory>

namespace CG{

    //small wrapper object for a texture buffer object
    //used to be able to have textures freed automatically
    //while still being able to pass them between materials
    class TexObj{
        unsigned int m_name{ 0 };

    public:
        TexObj(unsigned int name);

        ~TexObj();

        unsigned int getName() const;
    };

    class OpenGLMaterial : public Material{
    protected:
        //name of the stored shaderProgram
        GLuint m_program{ 0 };
        //a collection of shaderInformation that contains all stages of the shaderProgram
        std::vector<CG::ShaderInfo> m_shaders;

        //all texture object bound used by this object
        std::vector<std::shared_ptr<CG::TexObj>> m_texObjs;

        //the locations of all uniform variables in the shader program
        mutable std::map<std::string, GLint> m_uniforms;

        void(*m_uniformDataFunction)(const CG::OpenGLMaterial &material){
            [](const CG::OpenGLMaterial &material){ 
                glUniform4fv(material.getUniform("baseColor"), 1, material.getColor().data()); 
            }
        };

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

        
        std::vector<std::shared_ptr<CG::TexObj>>& getTextures();
        int getNumTextures() const;

        void setUniformDataFunction(void(*uniformDataFunction)(const CG::OpenGLMaterial &material));

        void setupUniformData() const;

        void addTexture(const char* filePath);

        void bindTextures() const;

        void unbindTextures() const;
    };

}


#endif