#include "GameEngine/Rendering/Texture2D.h"

#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>

#include "glm/gtc/type_ptr.hpp"

using namespace GameEngine::Rendering;

void Texture2D::CreateTexture(const TextureParams textureParams) const
{
    glTexImage2D(
                 GL_TEXTURE_2D,
                 0,
                 textureParams.InternalFormat,
                 static_cast<GLsizei>(_size.x),
                 static_cast<GLsizei>(_size.y),
                 0,
                 textureParams.Format,
                 textureParams.ChannelDataType,
                 _buffer);

    // Generate mip maps if needed
    if (textureParams.MipMapLevels > 0 && (textureParams.FilterMode == TextureFilterMode::LinearMipMap)) { glGenerateMipmap(GL_TEXTURE_2D); }
}

Texture2D::Texture2D(const std::string& filePath, const TextureParams textureParams):
    Texture(filePath, textureParams)
{
    // Extract name from path
    const size_t slashIndex  = filePath.find_last_of('/');
    const size_t periodIndex = filePath.find_last_of('.');
    _name                    = filePath.substr(slashIndex + 1, periodIndex - slashIndex - 1);

    CreateTexture(textureParams);
}

Texture2D::Texture2D(unsigned char* buffer, const glm::uvec2 size, const TextureParams textureParams):
    Texture(buffer, size, textureParams) { CreateTexture(textureParams); }

const std::string& Texture2D::GetName() const { return _name; }
