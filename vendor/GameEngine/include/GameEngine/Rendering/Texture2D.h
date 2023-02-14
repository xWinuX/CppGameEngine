#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/vec2.hpp>

#include "Texture.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Texture2D : public Texture<GL_TEXTURE_2D>
        {
            private:
                std::string _name;
                void CreateTexture(const TextureParams textureParams) const;

            public:
                explicit Texture2D(const std::string& filePath, const TextureParams textureParams = TextureParams());
                explicit Texture2D(unsigned char* buffer, const glm::uvec2 size, const TextureParams textureParams = TextureParams());
                const std::string& GetName() const;
        };
    }
}
