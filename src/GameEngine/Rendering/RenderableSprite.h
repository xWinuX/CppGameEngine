#pragma once
#include "Texture.h"
#include "glm/fwd.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace GameEngine
{
    namespace Rendering
    {
        class RenderableSprite
        {
            public:
                virtual                ~RenderableSprite() = default;
                virtual Texture*       GetTexture(const size_t frameIndex = 0) = 0;
                virtual unsigned char* GetQuadData(const size_t frameIndex = 0, const glm::mat4 transform = glm::identity<glm::mat4>()) = 0;
                virtual size_t         GetNumFrames() = 0;
        };
    }
}
