#include "GameEngine/Rendering/Texture.h"

#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>

using namespace GameEngine::Rendering;

Texture::Texture(const std::string& filePath, const ImportSettings importSettings)
{
    int width, height, bitsPerPixel;

    stbi_set_flip_vertically_on_load(1); // Flip texture upside down because opengl origin is bottom left
    unsigned char* const buffer = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, 4);

    _size.x = width;
    _size.y = height;

    GenerateTexture(buffer, importSettings);
}

Texture::Texture(unsigned char* buffer, const glm::uvec2 size, const ImportSettings importSettings):
    _size(size) { GenerateTexture(buffer, importSettings); }


void Texture::GenerateTexture(unsigned char* buffer, const Texture::ImportSettings importSettings)
{
    glGenTextures(1, &_textureID);

    glBindTexture(GL_TEXTURE_2D, _textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, importSettings.FilterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, importSettings.FilterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, importSettings.WrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, importSettings.WrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, importSettings.MipMapLevels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, importSettings.AnisotropyLevels);

    _buffer = buffer;
    glTexImage2D(GL_TEXTURE_2D, 0, importSettings.InternalFormat, static_cast<GLsizei>(_size.x), static_cast<GLsizei>(_size.y), 0, importSettings.Format,
                 importSettings.ChannelDataType, _buffer);
}


Texture::~Texture()
{
    glDeleteTextures(1, &_textureID);
    if (_buffer) { stbi_image_free(_buffer); }
}

void Texture::Bind(const unsigned slot = 0) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

const glm::uvec2& Texture::GetSize() const { return _size; }
stbi_uc*          Texture::GetBuffer() const { return _buffer; }
GLuint            Texture::GetTextureID() const { return _textureID; }
