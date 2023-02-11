#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/vec2.hpp>

#include "glm/vec4.hpp"
#include "glm/gtc/constants.hpp"
#include <stb_image.h>


namespace GameEngine
{
    namespace Rendering
    {
        enum TextureFilterMode
        {
            Linear  = GL_LINEAR,
            Nearest = GL_NEAREST,
        };

        enum TextureWrapMode
        {
            Clamp          = GL_CLAMP,
            ClampToEdge    = GL_CLAMP_TO_EDGE,
            ClampToBorder  = GL_CLAMP_TO_BORDER,
            Repeat         = GL_REPEAT,
            MirroredRepeat = GL_MIRRORED_REPEAT,
        };

        struct TextureParams
        {
            TextureFilterMode FilterMode       = TextureFilterMode::Linear;
            TextureWrapMode   WrapMode         = TextureWrapMode::Repeat;
            unsigned int      MipMapLevels     = 3;
            unsigned int      AnisotropyLevels = 8;
            GLenum            Format           = GL_RGBA;
            GLenum            InternalFormat   = GL_RGBA8;
            GLenum            ChannelDataType  = GL_UNSIGNED_BYTE;
            glm::vec4         BorderColor      = glm::vec4(1.0f);
        };

        template <GLenum TextureType>
        class Texture
        {
            public:
                void Bind(const unsigned int slot) const
                {
                    glActiveTexture(GL_TEXTURE0 + slot);
                    glBindTexture(TextureType, _textureID);
                }

                void Unbind()
                {
                    glBindTexture(TextureType, 0);
                }

                const glm::uvec2& GetSize() const { return _size; }
                unsigned char*    GetBuffer() const { return _buffer; }
                GLuint            GetTextureID() const { return _textureID; }

            protected:
                explicit Texture(const std::string& filePath, const TextureParams importSettings = TextureParams())
                {
                    int width, height, bitsPerPixel;

                    stbi_set_flip_vertically_on_load(1); // Flip texture upside down because opengl origin is bottom left
                    unsigned char* const buffer = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, 4);

                    _size.x = width;
                    _size.y = height;

                    CreateTextureAndSetParams(buffer, importSettings);
                }

                Texture(unsigned char* buffer, const glm::uvec2 size, const TextureParams importSettings = TextureParams()):
                    _size(size) { CreateTextureAndSetParams(buffer, importSettings); }

                void CreateTextureAndSetParams(unsigned char* buffer, const TextureParams importSettings)
                {
                    glGenTextures(1, &_textureID);

                    glBindTexture(TextureType, _textureID);

                    glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, importSettings.FilterMode);
                    glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, importSettings.FilterMode);
                    glTexParameteri(TextureType, GL_TEXTURE_WRAP_S, importSettings.WrapMode);
                    glTexParameteri(TextureType, GL_TEXTURE_WRAP_T, importSettings.WrapMode);
                    glTexParameteri(TextureType, GL_TEXTURE_MAX_LEVEL, importSettings.MipMapLevels);
                    glTexParameteri(TextureType, GL_TEXTURE_MAX_ANISOTROPY_EXT, importSettings.AnisotropyLevels);
                    glTexParameterfv(TextureType, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(importSettings.BorderColor));

                    _buffer = buffer;
                }

                GLuint         _textureID = 0;
                glm::uvec2     _size      = glm::zero<glm::uvec2>();
                unsigned char* _buffer    = nullptr;
        };
    }
}
