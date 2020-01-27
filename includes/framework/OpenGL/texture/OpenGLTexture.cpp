#include "OpenGLTexture.h"

CG::OpenGLTexture::OpenGLTexture() {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_name);
}

CG::OpenGLTexture::OpenGLTexture(GLenum type, int mipmapLevel) : m_type{type}, m_mipMapLevel{mipmapLevel} {
    glCreateTextures(type, 1, &m_name);
}

CG::OpenGLTexture::OpenGLTexture(const char* filePath) : OpenGLTexture() {
    loadFromFile(filePath);
}

CG::OpenGLTexture::OpenGLTexture(GLenum type, int mipmapLevel, const char* filePath) : OpenGLTexture(type, mipmapLevel) {
    loadFromFile(filePath);
}

CG::OpenGLTexture::~OpenGLTexture(){
    glDeleteTextures(1, &m_name);
}

unsigned int CG::OpenGLTexture::getName() const{
    return m_name;
}

void CG::OpenGLTexture::loadFromFile(const char* filePath){

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(0);

    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if(!data){
        std::cout << "Failed to load texture\n";
        stbi_image_free(data);
        return;
    }

    GLenum inputForm{ 0 };

    const char* lastDotOccurrence = strrchr(filePath, '.');
    if (strcmp(lastDotOccurrence, ".jpg") == 0) {
        inputForm = GL_RGB;
    }
    else if (strcmp(lastDotOccurrence, ".png") == 0) {
        inputForm = GL_RGBA;
    }
    else {
        std::cout << "Material doesnt know how to handle this file format.\n";
        stbi_image_free(data);
        return;
    }

    switch(m_type){
        
        case GL_TEXTURE_2D:
            glTextureStorage2D(m_name, 1, GL_RGB8, width, height);
            glTextureSubImage2D(m_name, m_mipMapLevel, 0, 0, width, height, inputForm, GL_UNSIGNED_BYTE, data);
            break;

        case GL_TEXTURE_CUBE_MAP:
            glTextureStorage2D(m_name, 1, GL_RGB8, width/4, height/3);

            assert("Faces of Cube Maps expect Textures to be squared" && (width/4) == (height/3));

            // width or height of a face in texels
            int faceSideLength{ width/ 4 };

            std::vector<std::vector<unsigned char>> faces;
            faces.resize(6);
            for(int i = 0; i< 6; ++i){
                faces[i].resize(faceSideLength*faceSideLength*nrChannels);
            }

            int midRowOffset{ width * faceSideLength * nrChannels };
            // width of a face taking color depth into account
            int faceWidth{ faceSideLength * nrChannels };
            // width of the texture taking color depth into account
            int textureWidth{ width * nrChannels };

            for(int row{ 0 }; row < faceSideLength; ++row){
                for(int col{ 0 }; col < faceSideLength; ++col){
                    for(int i{ 0 }; i < nrChannels; ++i){
                        faces[0][faceWidth*row+3*col+i] = data[midRowOffset + textureWidth*row + 3*faceWidth + 3*col + i];
                        faces[1][faceWidth*row+3*col+i] = data[midRowOffset + textureWidth*row + faceWidth + 3*col + i];
                        faces[4][faceWidth*row+3*col+i] = data[midRowOffset + textureWidth*row + 2*faceWidth + 3*col + i];
                        faces[5][faceWidth*row+3*col+i] = data[midRowOffset + textureWidth*row + 3*col + i];
                        faces[2][faceWidth*col+3*(faceSideLength-row)+i] = data[textureWidth*row + faceWidth + 3*col + i];
                        faces[3][faceWidth*(faceSideLength-col-1)+3*row+i] = data[2*midRowOffset + textureWidth*row + faceWidth + 3*col + i];
                    }
                }
            }

            for(int face = 0; face < 6; ++face){
                glTextureSubImage3D(m_name, 0, 0, 0, face, width/4, height/3, 1, inputForm, GL_UNSIGNED_BYTE, faces[face].data());
            }

            break;
    }

    glGenerateTextureMipmap(m_name);

    stbi_image_free(data);
}