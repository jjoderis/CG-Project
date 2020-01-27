#ifndef CG_FRAMEWORK_OPENGL_TEXTURE_OPENGLTEXTURE_H
#define CG_FRAMEWORK_OPENGL_TEXTURE_OPENGLTEXTURE_H

#include <GL/glew.h>
#include <stb_image.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>

namespace CG{
    //class that is supposed to make creating OpenGL textures more easy
    class OpenGLTexture{
        unsigned int m_name{ 0 };

        GLenum m_type{ GL_TEXTURE_2D };

        int m_mipMapLevel{ 0 };

    public:
        OpenGLTexture();

        OpenGLTexture(GLenum type, int mipmapLevel);

        OpenGLTexture(const char* filePath);

        OpenGLTexture(GLenum type, int mipmapLevel, const char* filePath);

        ~OpenGLTexture();

        unsigned int getName() const;

        void loadFromFile(const char* filePath);
    };

}

#endif