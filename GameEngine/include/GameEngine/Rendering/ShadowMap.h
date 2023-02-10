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
                glm::uvec2   _size;
                glm::vec3    _position;
                glm::mat4    _projection;

            public:
                explicit ShadowMap(glm::uvec2 size);
                void     Bind() const;
                Texture* GetTexture() const;
                void     Unbind() const;
 
                void SetPosition(glm::vec3 position);
                void SetProjection(glm::mat4 projection);
                
                glm::vec3 GetPosition() const;
                glm::mat4 GetProjection() const;
        };
    }
}
