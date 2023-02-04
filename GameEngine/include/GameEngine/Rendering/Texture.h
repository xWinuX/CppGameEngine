#pragma once
#include <string>
#include <tiny_gltf.h>
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/gtc/constants.hpp>

#include "Sampler.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Texture : public Sampler
        {
            public:
                enum FilterMode
                {
                    Linear  = GL_LINEAR,
                    Nearest = GL_NEAREST,
                };

                enum WrapMode
                {
                    Clamp          = GL_CLAMP,
                    ClampToEdge    = GL_CLAMP_TO_EDGE,
                    Repeat         = GL_REPEAT,
                    MirroredRepeat = GL_MIRRORED_REPEAT,
                };

                struct ImportSettings
                {
                    Texture::FilterMode FilterMode       = Texture::FilterMode::Linear;
                    Texture::WrapMode   WrapMode         = Texture::WrapMode::Repeat;
                    unsigned int        MipMapLevels     = 3;
                    unsigned int        AnisotropyLevels = 8;
                    GLenum              Format           = GL_RGBA;
                    GLenum              InternalFormat   = GL_RGBA8;
                    GLenum              ChannelDataType  = GL_UNSIGNED_BYTE;
                };

                explicit Texture(const std::string& filePath, ImportSettings importSettings = ImportSettings());
                explicit Texture(unsigned char* buffer, glm::uvec2 size, ImportSettings importSettings = ImportSettings());
                ~Texture();

                void Bind(const unsigned int slot) const override;
                void Unbind() override;

                const glm::uvec2& GetSize() const;
                unsigned char*    GetBuffer() const;
                GLuint            GetTextureID() const;

            private:
                GLuint         _textureID = 0;
                glm::uvec2     _size      = glm::zero<glm::uvec2>();
                unsigned char* _buffer    = nullptr;

                void GenerateTexture(unsigned char* buffer, ImportSettings importSettings);
        };
    }
}
