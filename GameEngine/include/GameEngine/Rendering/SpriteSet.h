#pragma once
#include <vector>

#include "RenderableSprite.h"
#include "Texture.h"

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
                explicit SpriteSet(Texture* texture);
                SpriteSet(Texture* texture, unsigned int numFrames, glm::uvec2 frameSize);
                SpriteSet(Texture* texture, const msdf_atlas::FontGeometry& fontGeometry);

                ~SpriteSet() override;

                Sprite* GetSprite(size_t frameIndex) const;

                size_t         GetNumFrames() override;
                Texture*       GetTexture(size_t frameIndex = 0) override;
                unsigned char* GetQuadDataWithTransform(size_t frameIndex = 0, const glm::mat4 transform = glm::identity<glm::mat4>()) override;
                unsigned char* GetQuadData(const size_t frameIndex = 0) override;

            private:
                std::vector<Sprite*> _sprites;
        };
    }
}
