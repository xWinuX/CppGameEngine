#pragma once
#include <vector>

#include "Texture.h"
#include "VertexArrayObject.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace GameEngine
{
    namespace Rendering
    {
        class Sprite
        {
            private:
                struct VertexData
                {
                    int       VertexIndex;
                    float     AspectRatio;
                    glm::vec2 UV;
                    glm::vec4 Color;
                };

                void AddSpriteQuad(const float aspectRatio, const glm::vec2 uvStep, const glm::uvec2 offset);

                Texture*                  _texture;
                glm::uvec2                _frameSize;
                std::vector<glm::uvec2>   _framePositions;
                std::vector<VertexData>   _vertexData;
                std::vector<unsigned int> _indices;
                unsigned int              _numFrames         = 1;
                VertexArrayObject*        _vertexArrayObject = nullptr;

            public:
                explicit Sprite(Texture* texture);
                Sprite(Texture* texture, unsigned int numFrames, glm::uvec2 frameSize);

                void Finalize();

                VertexArrayObject*             GetVertexArrayObject() const;
                Texture*                       GetTexture() const;
                unsigned int                   GetNumFrames() const;
                glm::uvec2                     GetFrameSize() const;
                const std::vector<glm::uvec2>& GetFramePositions();
                void ChangeFrameUV(unsigned int frameIndex, glm::vec2 topLeftUV, glm::vec2 bottomRightUV);
        };
    }
}
