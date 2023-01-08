#include "Texture.h"

#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/constants.hpp>
#include <stb_image.h>

using namespace GameEngine::Rendering;

Texture::Texture(std::string filePath) :
    _textureID(0),
    _filePath(std::move(filePath)),
    _size(glm::zero<glm::ivec2>()),
    _bitsPerPixel(0)
{
    stbi_set_flip_vertically_on_load(1); // Flip texture upside down because opengl origin is bottom left
    stbi_uc* const localBuffer = stbi_load(_filePath.c_str(), &_size.x, &_size.y, &_bitsPerPixel, 4);

    glGenTextures(1, &_textureID);

    glBindTexture(GL_TEXTURE_2D, _textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
    
    // delete local buffer again
    if (localBuffer) { stbi_image_free(localBuffer); }
}

Texture::~Texture()
{
    glDeleteTextures(1, &_textureID);
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

const glm::ivec2& Texture::GetSize() const { return _size; }
