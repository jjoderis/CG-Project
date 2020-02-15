#include "shader.h"

GLuint CG::createShaderProgram(std::vector<CG::ShaderInfo> &shaders){
    std::vector<CG::ShaderInfo> empty;
    return updateShaderProgram(0, shaders, empty);
}

GLuint CG::updateShaderProgram(GLuint program, std::vector<CG::ShaderInfo> &shaders, std::vector<CG::ShaderInfo> &newShaders){

    if(!(shaders.size() + newShaders.size())){
        return 0;
    }

    if(!program) {
        program = glCreateProgram();
    }

    if(!program){
        std::cerr << "Unable to create shader program\n";
        return 0;
    }

    for(ShaderInfo &newEntry : newShaders){
        bool added = false;
        for(unsigned int i = 0; i < shaders.size(); ++i) {
            if(newEntry.type == shaders[i].type){
                glDetachShader(program, shaders[i].shader);
                glDeleteShader(shaders[i].shader);
                shaders[i] = newEntry;
                added = true;
                break;
            }
        }
        if(!added){
            shaders.emplace_back(newEntry);
        }
    }

    for(ShaderInfo &entry : shaders){
        if(!entry.shader){
            entry.shader = glCreateShader(entry.type);

            if(entry.isFile){
                entry.shaderData = readTextFile(entry.shaderData.c_str());
                entry.isFile = false;
            }
            
            const char* shaderText = entry.shaderData.c_str();
            glShaderSource(entry.shader, 1, &shaderText, 0);

            glCompileShader(entry.shader);

            GLint compiled;
            glGetShaderiv( entry.shader, GL_COMPILE_STATUS, &compiled );
            if ( !compiled ) {
                GLsizei len;
                glGetShaderiv( entry.shader, GL_INFO_LOG_LENGTH, &len );

                GLchar* log = new GLchar[len+1];
                glGetShaderInfoLog( entry.shader, len, &len, log );
                std::cerr << "Shader compilation failed: " << log << std::endl;
                delete [] log;

                assert(false);
                return 0;
            }

            glAttachShader(program, entry.shader);
        }
    }

    glLinkProgram(program);

    GLint linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        GLsizei len;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

        GLchar* log = new GLchar[len+1];
        glGetProgramInfoLog( program, len, &len, log );
        std::cerr << "Shader linking failed: " << log << std::endl;
        delete [] log;

        for (ShaderInfo &entry : shaders) {
            glDeleteShader( entry.shader );
            entry.shader = 0;
        }
        
        assert(false);
        return 0;
    }

    return program;
}