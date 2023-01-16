#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/vec2.hpp>

#include "stb_image.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Texture
        {
            public:
                enum FilterMode
                {
                    Linear = GL_LINEAR,
                    Nearest = GL_NEAREST,
                };

                enum WrapMode
                {
                    Clamp = GL_CLAMP,
                    Repeat = GL_REPEAT,
                    MirroredRepeat = GL_MIRRORED_REPEAT,
                };

                struct ImportSettings
                {
                    Texture::FilterMode FilterMode       = Texture::FilterMode::Linear;
                    Texture::WrapMode   WrapMode         = Texture::WrapMode::Repeat;
                    unsigned int        MipMapLevels     = 3;
                    unsigned int        AnisotropyLevels = 8;
                };

                explicit Texture(std::string filePath, ImportSettings importSettings = ImportSettings());
                ~Texture();

                void        Bind(unsigned int slot) const;
                static void Unbind();

                const glm::uvec2& GetSize() const;
                stbi_uc* GetBuffer() const;

            private:
                GLuint      _textureID;
                std::string _filePath;
                glm::uvec2  _size;
                int         _bitsPerPixel;
                stbi_uc*    _buffer;
        };
    }
}
