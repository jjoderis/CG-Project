#include "OpenGLMaterial.h"

CG::OpenGLMaterial::OpenGLMaterial(const std::string vertexShaderData, const std::string fragmentShaderData){
    m_shaders.emplace_back(
        ShaderInfo{
            GL_VERTEX_SHADER,
            vertexShaderData,
            0u
        }
    );

    m_shaders.emplace_back(
        ShaderInfo{
            GL_FRAGMENT_SHADER,
            fragmentShaderData,
            0u
        }
    );

    m_program = CG::createShaderProgram(m_shaders);
    getUniformLocs();
}

CG::OpenGLMaterial::OpenGLMaterial(const CG::RGBA_Color &color) : OpenGLMaterial(){
    setColor(color);
}

CG::OpenGLMaterial::OpenGLMaterial()
    : OpenGLMaterial(
        R"(
            #version 450 core

            layout (location = 0) in vec4 vPosition;

            uniform mat4 modelViewMatrix;
            uniform mat4 projectionMatrix;

            void main(){
                gl_Position = projectionMatrix * modelViewMatrix * vPosition;
            }
        )",
        R"(
            #version 450 core

            uniform vec4 baseColor;

            layout (location = 0) out vec4 fColor;

            void main(){
                fColor= baseColor;
            }
        )"
    ) 
{}

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
    for(const ShaderInfo &entry : other.m_shaders){
        m_shaders.emplace_back(
            ShaderInfo{
                entry.type,
                entry.shaderData,
                0
            }
        );
    }
    m_program = CG::createShaderProgram(m_shaders);
    getUniformLocs();
    getUniformLocs();

    return *this;
}

void CG::OpenGLMaterial::setVertexShader(const std::string shaderData){
    std::vector<ShaderInfo> newShader{
        ShaderInfo{
            GL_VERTEX_SHADER,
            shaderData,
            0
        }
    };

    m_program = CG::updateShaderProgram(m_program, m_shaders, newShader);
    getUniformLocs();
}

void CG::OpenGLMaterial::setTesselationControlShader(const std::string shaderData){
    std::vector<ShaderInfo> newShader{
        ShaderInfo{
            GL_TESS_CONTROL_SHADER,
            shaderData,
            0
        }
    };

    m_program = CG::updateShaderProgram(m_program, m_shaders, newShader);
    getUniformLocs();
}

void CG::OpenGLMaterial::setTesselationEvaluationShader(const std::string shaderData){
    std::vector<ShaderInfo> newShader{
        ShaderInfo{
            GL_TESS_EVALUATION_SHADER,
            shaderData,
            0
        }
    };

    m_program = CG::updateShaderProgram(m_program, m_shaders, newShader);
    getUniformLocs();
}

void CG::OpenGLMaterial::setGeometryShader(const std::string shaderData){
    std::vector<ShaderInfo> newShader{
        ShaderInfo{
            GL_GEOMETRY_SHADER,
            shaderData,
            0
        }
    };

    m_program = CG::updateShaderProgram(m_program, m_shaders, newShader);
    getUniformLocs();
}

void CG::OpenGLMaterial::setFragmentShader(const std::string shaderData){
    std::vector<ShaderInfo> newShader{
        ShaderInfo{
            GL_FRAGMENT_SHADER,
            shaderData,
            0
        }
    };

    m_program = CG::updateShaderProgram(m_program, m_shaders, newShader);
    getUniformLocs();
}

void CG::OpenGLMaterial::getUniformLocs(){
    uniformLocs.baseColor = glGetUniformLocation(m_program, "baseColor");
    uniformLocs.modelViewMatrix = glGetUniformLocation(m_program, "modelViewMatrix");
    uniformLocs.projectionMatrix = glGetUniformLocation(m_program, "projectionMatrix");
    uniformLocs.normalMatrix = glGetUniformLocation(m_program, "normalMatrix");
    uniformLocs.shininess = glGetUniformLocation(m_program, "shininess");
    uniformLocs.modelMatrix = glGetUniformLocation(m_program, "modelMatrix");
    uniformLocs.viewMatrix = glGetUniformLocation(m_program, "viewMatrix");
}

int CG::OpenGLMaterial::getProgram() const{
    return m_program;
}

