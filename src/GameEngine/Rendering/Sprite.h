#pragma once

#include "RenderableSprite.h"
#include "Texture.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

namespace GameEngine
{
    namespace Rendering
    {
        class Sprite : public RenderableSprite
        {
            public:
                struct QuadData
                {
                    glm::mat4 Transform;
                    glm::vec2 Position0;
                    glm::vec2 UV0;
                    glm::vec2 Position1;
                    glm::vec2 UV1;
                    glm::vec2 Position2;
                    glm::vec2 UV2;
                    glm::vec2 Position3;
                    glm::vec2 UV3;
                    glm::vec4 Colors[4];
                };

                explicit Sprite(Texture* texture, unsigned int pixelsPerUnit = 1);
                Sprite(Texture* texture, glm::uvec2 pixelPosition, glm::uvec2 size, glm::vec2 uvTopLeft, glm::vec2 uvBottomRight, unsigned int pixelsPerUnit = 1);
                Sprite(Texture* texture, glm::uvec2 pixelPosition, glm::vec4 positionRightTopLeftBottom, glm::vec2 uvTopLeft, glm::vec2 uvBottomRight, unsigned int pixelsPerUnit = 1);
                ~Sprite() override;

                void SetUV(glm::vec2 topLeftUV, glm::vec2 bottomRightUV) const;
                void SetTexture(Texture* texture);
                void SetTrs(glm::mat4 trs) const;


                size_t         GetNumFrames() override;
                QuadData*      GetQuadDataPtr() const;
                unsigned char* GetQuadDataWithTransform(const size_t frameIndex = 0, const glm::mat4 transform = glm::identity<glm::mat4>()) override;
                unsigned char* GetQuadData(const size_t frameIndex = 0) override;
                Texture*       GetTexture(const size_t frameIndex = 0) override;
                float          GetPixelsPerUnitFactor() const;


                Texture*   GetSourceTexture() const;
                glm::vec2  GetPixelPosition() const;
                glm::uvec2 GetSize() const;

            private:
                Texture*     _sourceTexture;
                Texture*     _texture;
                glm::uvec2   _pixelPosition;
                glm::uvec2   _size;
                unsigned int _pixelsPerUnit;
                float        _pixelsPerUnitFactor;
                QuadData*    _quadData = nullptr;

                void CreateSpriteQuad(const glm::vec2 uvTopLeft, const glm::vec2 uvBottomRight, const glm::vec2 origin = glm::zero<glm::vec2>());
        };
    }
}
