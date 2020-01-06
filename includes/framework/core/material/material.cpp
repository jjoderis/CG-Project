#include "material.h"

CG::Material::Material(const char* vertexShaderData, const char* fragmentShaderData){
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

CG::Material::Material()
    : Material(
        R"(
            #version 450 core

            layout (location = 0) in vec4 vPosition;

            void main(){
                gl_Position = vPosition;
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
    ) {}

CG::Material::Material(CG::RGBA_Color color) : Material() {
    m_color = color;
}

CG::Material::Material(CG::RGB_Color color) : Material(CG::RGBA_Color(color, 1.0)) {}

CG::Material::Material(const CG::Material &other) : m_color{ other.m_color }{
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
}

CG::Material& CG::Material::operator= (const CG::Material &other){
    m_color = other.m_color;
    m_shaders = other.m_shaders;
    m_program = CG::createShaderProgram(m_shaders);
    getUniformLocs();

    return *this;
}

CG::Material::~Material(){
    for(ShaderInfo &entry : m_shaders){
        glDeleteShader(entry.shader);
    }

    glDeleteProgram(m_program);
}

void CG::Material::setVertexShader(const char* shaderData){
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

void CG::Material::setTesselationControlShader(const char* shaderData){
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

void CG::Material::setTesselationEvaluationShader(const char* shaderData){
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

void CG::Material::setGeometryShader(const char* shaderData){
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

void CG::Material::setFragmentShader(const char* shaderData){
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

void CG::Material::getUniformLocs(){
    uniformLocs.baseColor = glGetUniformLocation(m_program, "baseColor");
    uniformLocs.worldMatrix = glGetUniformLocation(m_program, "worldMatrix");
}

void CG::Material::setColor(CG::RGB_Color color){
    m_color = CG::RGBA_Color{color, 1.0};
}

void CG::Material::setColor(GLfloat r, GLfloat g, GLfloat b){
    m_color = CG::RGBA_Color{ r, g, b, 1.0 };
}

void CG::Material::setColor(CG::RGBA_Color color){
    m_color = color;
}

void CG::Material::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    m_color = CG::RGBA_Color{ r, g, b, a };
}

void CG::Material::use(){
    glUseProgram(m_program);
    glUniform4fv(uniformLocs.baseColor, 1, m_color.data());
}