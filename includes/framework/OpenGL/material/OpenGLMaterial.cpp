#include "OpenGLMaterial.h"

CG::OpenGLMaterial::OpenGLMaterial(const std::initializer_list<CG::ShaderInfo> &shaderData){
    m_shaders = shaderData;

    m_program = CG::createShaderProgram(m_shaders);
}

CG::OpenGLMaterial::OpenGLMaterial(const CG::RGBA_Color &color) : OpenGLMaterial(){
    setColor(color);
}

CG::OpenGLMaterial::OpenGLMaterial()
    : OpenGLMaterial{
        CG::ShaderInfo{
            GL_VERTEX_SHADER,
             R"(
                #version 450 core

                layout (location = 0) in vec4 vPosition;

                uniform mat4 modelViewMatrix;
                uniform mat4 projectionMatrix;

                void main(){
                    gl_Position = projectionMatrix * modelViewMatrix * vPosition;
                }
            )",
            false,
            0u
        },
        CG::ShaderInfo{
            GL_FRAGMENT_SHADER,
            R"(
                #version 450 core

                uniform vec4 baseColor;

                layout (location = 0) out vec4 fColor;

                void main(){
                    fColor= baseColor;
                }
            )",
            false,
            0u
        }
    }
{
}

CG::OpenGLMaterial::~OpenGLMaterial(){
    for(ShaderInfo &entry : m_shaders){
        glDeleteShader(entry.shader);
    }

    glDeleteProgram(m_program);
}

CG::OpenGLMaterial::OpenGLMaterial(const OpenGLMaterial &other) : Material{ other }{
    *this = other;
}


CG::OpenGLMaterial& CG::OpenGLMaterial::operator= (const OpenGLMaterial &other){
    
    if(&other == this){
        return *this;
    }

    for(const ShaderInfo &entry : other.m_shaders){
        m_shaders.emplace_back(
            ShaderInfo{
                entry.type,
                entry.shaderData,
                entry.isFile,
                0
            }
        );
    }

    m_program = CG::createShaderProgram(m_shaders);
    m_textures = other.m_textures;
    
    return *this;
}

void CG::OpenGLMaterial::setVertexShader(const std::string shaderData, bool isFile){
    std::vector<ShaderInfo> newShader{
        ShaderInfo{
            GL_VERTEX_SHADER,
            shaderData,
            isFile,
            0
        }
    };

    m_program = CG::updateShaderProgram(m_program, m_shaders, newShader);
}

void CG::OpenGLMaterial::setTesselationControlShader(const std::string shaderData, bool isFile){
    std::vector<ShaderInfo> newShader{
        ShaderInfo{
            GL_TESS_CONTROL_SHADER,
            shaderData,
            isFile,
            0
        }
    };

    m_program = CG::updateShaderProgram(m_program, m_shaders, newShader);
}

void CG::OpenGLMaterial::setTesselationEvaluationShader(const std::string shaderData, bool isFile){
    std::vector<ShaderInfo> newShader{
        ShaderInfo{
            GL_TESS_EVALUATION_SHADER,
            shaderData,
            isFile,
            0
        }
    };

    m_program = CG::updateShaderProgram(m_program, m_shaders, newShader);
}

void CG::OpenGLMaterial::setGeometryShader(const std::string shaderData, bool isFile){
    std::vector<ShaderInfo> newShader{
        ShaderInfo{
            GL_GEOMETRY_SHADER,
            shaderData,
            isFile,
            0
        }
    };

    m_program = CG::updateShaderProgram(m_program, m_shaders, newShader);
}

void CG::OpenGLMaterial::setFragmentShader(const std::string shaderData, bool isFile){
    std::vector<ShaderInfo> newShader{
        ShaderInfo{
            GL_FRAGMENT_SHADER,
            shaderData,
            isFile,
            0
        }
    };

    m_program = CG::updateShaderProgram(m_program, m_shaders, newShader);
}

GLint CG::OpenGLMaterial::getUniform(const char* name) const{
    return getUniform(std::string(name));
}

GLint CG::OpenGLMaterial::getUniform(const std::string &name) const
{
    auto iter{ m_uniforms.find(name) };
    if(iter == m_uniforms.end()){
        m_uniforms.insert({name, glGetUniformLocation(m_program, name.c_str())});
        iter = m_uniforms.find(name);
    }
    return iter->second;
}


int CG::OpenGLMaterial::getProgram() const{
    return m_program;
}

std::vector<std::shared_ptr<CG::OpenGLTexture>>& CG::OpenGLMaterial::getTextures(){
    return m_textures;
}

int CG::OpenGLMaterial::getNumTextures() const{
    return m_textures.size();
}


void CG::OpenGLMaterial::setupUniformData() const{
    glUniform4fv(getUniform("baseColor"), 1, m_color.data());
    glUniform1f(getUniform("shininess"), m_shininess);
}

void CG::OpenGLMaterial::addTexture(std::shared_ptr<CG::OpenGLTexture> texture){
    assert("We only allow 16 textures per material" && m_textures.size() < 16);

    m_textures.emplace_back(texture);
}

void CG::OpenGLMaterial::bindTextures() const{
    for(unsigned int i = 0; i < m_textures.size(); ++i){
        glBindTextureUnit(i, m_textures[i]->getName());
    }
}

void CG::OpenGLMaterial::unbindTextures() const{
    for(unsigned int i = 0; i < m_textures.size(); ++i){
        glBindTextureUnit(i, 0);
    }
}
