#pragma once
#include <vector>

#include "RenderableSprite.h"
#include "Sprite.h"
#include "Texture2D.h"

#include "glm/mat4x4.hpp"
#include "msdf-atlas-gen/FontGeometry.h"
#include "msdf-atlas-gen/GlyphGeometry.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Sprite;

        class SpriteSet : public RenderableSprite
        {
            public:
                explicit SpriteSet(Texture2D* texture, Sprite::AdditionalInfo additionalInfo = Sprite::AdditionalInfo());
                SpriteSet(Texture2D* texture, unsigned int numFrames, glm::uvec2 frameSize, Sprite::AdditionalInfo additionalInfo = Sprite::AdditionalInfo());
                SpriteSet(Texture2D* texture, const msdf_atlas::FontGeometry& fontGeometry, Sprite::AdditionalInfo additionalInfo = Sprite::AdditionalInfo());

                ~SpriteSet() override;

                Sprite* GetSprite(size_t frameIndex) const;

                size_t         GetNumFrames() override;
                Texture2D*     GetTexture(size_t frameIndex = 0) override;
                unsigned char* GetQuadDataWithTransform(size_t frameIndex = 0, const glm::mat4 transform = glm::identity<glm::mat4>()) override;
                unsigned char* GetQuadData(const size_t frameIndex = 0) override;

            private:
                std::vector<Sprite*> _sprites;
        };
    }
}
