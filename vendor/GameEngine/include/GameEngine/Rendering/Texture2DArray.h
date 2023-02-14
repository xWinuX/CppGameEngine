#pragma once
#include "Texture.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Texture2DArray final : public Texture<GL_TEXTURE_2D_ARRAY>
        {
            public:
                explicit Texture2DArray(const glm::uvec2 size, const int depth, const TextureParams textureParams = TextureParams());
            
        };
    }
}
