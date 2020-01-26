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

    //glDeleteTextures(m_texObjs.size(), m_texObjs.data());

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
    m_texObjs = other.m_texObjs;
    m_uniformDataFunction = other.m_uniformDataFunction;
    
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

std::vector<unsigned int>& CG::OpenGLMaterial::getTextures(){
    return m_texObjs;
}

int CG::OpenGLMaterial::getNumTextures() const{
    return m_texObjs.size();
}

void CG::OpenGLMaterial::setUniformDataFunction(void(*uniformDataFunction)(const CG::OpenGLMaterial &material)){
    m_uniformDataFunction = uniformDataFunction;
}

void CG::OpenGLMaterial::setupUniformData() const{
    m_uniformDataFunction(*this);
}

void CG::OpenGLMaterial::addTexture(const char* filePath){
    assert("We only allow 16 textures per material" && m_texObjs.size() < 16);

    unsigned int texObj{ 0 };

    glCreateTextures(GL_TEXTURE_2D, 1, &texObj);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(0);

    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if(data) {
        const char* lastDotOccurrence = strrchr(filePath, '.');
        if (strcmp(lastDotOccurrence, ".jpg") == 0) {
            
            glTextureStorage2D(texObj, 1, GL_RGB8, width, height);
            glTextureSubImage2D(texObj, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if (strcmp(lastDotOccurrence, ".png") == 0) {
            glTextureStorage2D(texObj, 1, GL_RGB8, width, height);
            glTextureSubImage2D(texObj, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Material doesnt know how to handle this file format.\n";
            stbi_image_free(data);
            return;
        }
    }
    else {
        std::cout << "Failed to load texture\n";
        stbi_image_free(data);
        return;
    }
    stbi_image_free(data);
    m_texObjs.emplace_back(texObj);
}

void CG::OpenGLMaterial::bindTextures() const{
    for(unsigned int i = 0; i < m_texObjs.size(); ++i){
        glBindTextureUnit(i, m_texObjs[i]);
    }
}

void CG::OpenGLMaterial::unbindTextures() const{
    for(unsigned int i = 0; i < m_texObjs.size(); ++i){
        glBindTextureUnit(i, 0);
    }
}
