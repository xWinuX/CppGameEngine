#pragma once
#include "Texture2DArray.h"
#include "GameEngine/Rendering/FrameBuffer.h"
#include "GameEngine/Rendering/Shader.h"

namespace GameEngine
{
    namespace Rendering
    {
        class CascadedShadowMap
        {
            public:
                explicit        CascadedShadowMap(glm::uvec2 size);
                void            Bind() const;
                Texture2DArray* GetTexture() const;
                void            Unbind() const;

                void SetProjection(glm::mat4 projection);

                glm::mat4 GetProjection() const;

            private:
                Texture2DArray* _shadowMap;
                FrameBuffer*    _shadowDepthMap;
                glm::uvec2      _size;
                glm::mat4       _projection = glm::identity<glm::mat4>();
        };
    }
}
