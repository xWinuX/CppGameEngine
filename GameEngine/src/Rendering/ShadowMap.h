#pragma once
#include "GameEngine/Rendering/FrameBuffer.h"
#include "GameEngine/Rendering/Shader.h"

namespace GameEngine
{
    namespace Rendering
    {
        class ShadowMap
        {
            private:
                Texture*     _shadowMap;
                FrameBuffer* _shadowDepthMap;

            public:
                explicit ShadowMap(glm::uvec2 size);
        };
    }
}
