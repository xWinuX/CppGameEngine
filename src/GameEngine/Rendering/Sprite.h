#pragma once
#include <vector>

#include "Texture.h"
#include "VertexArrayObject.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

namespace GameEngine
{
    namespace Rendering
    {
        class Sprite
        {
            public:
                struct QuadData
                {
                    // Divisor 1
                    float     AspectRatio;
                    glm::mat4 Transform;

                    // Divisor 1
                    glm::vec2 UVs[4];
                    glm::vec4 Colors[4];
                };

                explicit Sprite(Texture* texture);
                Sprite(Texture* texture, unsigned int numFrames, glm::uvec2 frameSize);

                void Finalize();

                void ChangeFrameUV(size_t frameIndex, glm::vec2 topLeftUV, glm::vec2 bottomRightUV);
                void ChangeFrameTexture(size_t frameIndex, Texture* texture);
                void SetQuadTransform(size_t frameIndex, glm::mat4 trs);

                unsigned char* GetQuadData(const size_t frameIndex = 0);

                Texture*                       GetSourceTexture() const;
                VertexArrayObject*             GetVertexArrayObject() const;
                unsigned int                   GetNumFrames() const;
                glm::uvec2                     GetFrameSize() const;
                const std::vector<Texture*>&   GetTextures() const;
                const std::vector<glm::uvec2>& GetFramePositions();

            private:
                void AddSpriteQuad(const float aspectRatio, const glm::vec2 uvStep, const glm::uvec2 offset);

                Texture*                  _sourceTexture;
                glm::uvec2                _frameSize;
                std::vector<Texture*>     _textures;
                std::vector<glm::uvec2>   _framePositions;
                std::vector<QuadData>   _quadData;
                std::vector<unsigned int> _indices;
                unsigned int              _numFrames         = 1;
                VertexArrayObject*        _vertexArrayObject = nullptr;
        };
    }
}
