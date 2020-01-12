#ifndef CG_FRAMEWORK_CORE_SHADER_SHADER_H
#define CG_FRAMEWORK_CORE_SHADER_SHADER_H

#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <string>

namespace CG{
    // Taken from code in this repository https://github.com/openglredbook/examples/tree/master/src
    typedef struct {
        GLenum       type;
        std::string  shaderData; //string containing shader code or string containing path to file with shader code
        GLuint       shader;
    } ShaderInfo;

    //Creates a new shaderProgram using the given shaderData; returns the name of the created program
    GLuint createShaderProgram(std::vector<ShaderInfo> &shaders);

    //updates the given shaderProgram or creates a new one if none was given using the information about the current and new shaders
    GLuint updateShaderProgram(GLuint program, std::vector<ShaderInfo> &oldShaders, std::vector<ShaderInfo> &newShaders);
}

#endif