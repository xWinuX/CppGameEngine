#include "GameEngine/Rendering/Texture2DArray.h"

GameEngine::Rendering::Texture2DArray::Texture2DArray(const glm::uvec2 size, const int depth, const TextureParams textureParams):
    Texture(size, textureParams)
{
    glTexImage3D(
                 GL_TEXTURE_2D_ARRAY,
                 0,
                 textureParams.InternalFormat,
                 static_cast<GLsizei>(_size.x),
                 static_cast<GLsizei>(_size.y),
                 depth,
                 0,
                 textureParams.Format,
                 textureParams.ChannelDataType,
                 nullptr
                );
}
