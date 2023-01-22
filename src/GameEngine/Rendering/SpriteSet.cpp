#include "SpriteSet.h"

#include "Sprite.h"

#include "glm/ext/matrix_transform.hpp"

using namespace GameEngine::Rendering;

SpriteSet::SpriteSet(Texture* texture) { _sprites.push_back(new Sprite(texture)); }

SpriteSet::SpriteSet(Texture* texture, const unsigned int numFrames, const glm::uvec2 frameSize)
{
    const float uStep = 1.0f / static_cast<float>(numFrames);
    for (unsigned int i = 0; i < numFrames; i++)
    {
        const glm::vec2 uvTopLeft     = glm::vec2(uStep * static_cast<float>(i), 1.0f);
        const glm::vec2 uvBottomRight = glm::vec2(uStep * static_cast<float>(i + 1), 1.0f);

        _sprites.push_back(new Sprite(texture, glm::uvec2(static_cast<unsigned int>(frameSize.x) * i, 0), frameSize, uvTopLeft, uvBottomRight));
    }
}

SpriteSet::SpriteSet(Texture* texture, const std::vector<msdf_atlas::GlyphGeometry>& glyphs)
{
    const glm::vec2 uvStep = glm::vec2(1.0f / static_cast<float>(texture->GetSize().x), 1.0f / static_cast<float>(texture->GetSize().y));

    for (const msdf_atlas::GlyphBox glyph : glyphs)
    {
        const glm::vec2 uvTopLeft     = glm::vec2(uvStep.x * static_cast<float>(glyph.rect.x), uvStep.y * static_cast<float>(glyph.rect.y));
        const glm::vec2 uvBottomRight = glm::vec2(uvTopLeft.x + static_cast<float>(glyph.rect.w) * uvStep.x, uvTopLeft.y + static_cast<float>(glyph.rect.h) * uvStep.y);

        _sprites.push_back(new Sprite(texture, glm::uvec2(glyph.rect.x, glyph.rect.y), glm::uvec2(glyph.rect.w, glyph.rect.h), uvTopLeft, uvBottomRight));
    }
}

SpriteSet::~SpriteSet() { for (const Sprite* sprite : _sprites) { delete sprite; } }

Sprite*        SpriteSet::GetSprite(const size_t frameIndex) const { return _sprites[frameIndex]; }
size_t         SpriteSet::GetNumFrames() { return _sprites.size(); }
Texture*       SpriteSet::GetTexture(const size_t frameIndex) { return _sprites[frameIndex]->GetTexture(); }
unsigned char* SpriteSet::GetQuadData(const size_t frameIndex, const glm::mat4 transform) { return _sprites[frameIndex]->GetQuadData(0, transform); }
