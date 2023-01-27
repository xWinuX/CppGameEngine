#include <GameEngine/Rendering/SpriteSet.h>
#include <GameEngine/Rendering/Sprite.h>

#include <iostream>
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

SpriteSet::SpriteSet(Texture* texture, const msdf_atlas::FontGeometry& fontGeometry)
{
    const glm::vec2 texelSize = glm::vec2(1.0f / static_cast<float>(texture->GetSize().x), 1.0f / static_cast<float>(texture->GetSize().y));

    const auto glyphs = fontGeometry.getGlyphs();

    for (const msdf_atlas::GlyphGeometry& glyph : glyphs)
    {
        double pl, pb, pr, pt;
        double il, ib, ir, it;
        glyph.getQuadPlaneBounds(pl, pb, pr, pt);
        glyph.getQuadAtlasBounds(il, ib, ir, it);

        std::cout << "left" << pl << std::endl;
        std::cout << "right" << pr << std::endl;
        std::cout << "top" << pt << std::endl;
        std::cout << "bottom" << pb << std::endl;

        const glm::uvec2 pixelPosition = glm::uvec2(il, it);

        il *= texelSize.x;
        ib *= texelSize.y;
        ir *= texelSize.x;
        it *= texelSize.y;
        
        const glm::vec2 uvTopLeft     = glm::vec2(il, it);
        const glm::vec2 uvBottomRight = glm::vec2(ir, ib);

        _sprites.push_back(new Sprite(texture, pixelPosition, glm::vec4(pl, pr, pt, pb), uvTopLeft, uvBottomRight));
    }
}

SpriteSet::~SpriteSet() { for (const Sprite* sprite : _sprites) { delete sprite; } }

Sprite*        SpriteSet::GetSprite(const size_t frameIndex) const { return _sprites[frameIndex]; }
size_t         SpriteSet::GetNumFrames() { return _sprites.size(); }
Texture*       SpriteSet::GetTexture(const size_t frameIndex) { return _sprites[frameIndex]->GetTexture(); }
unsigned char* SpriteSet::GetQuadDataWithTransform(const size_t frameIndex, const glm::mat4 transform) { return _sprites[frameIndex]->GetQuadDataWithTransform(0, transform); }
unsigned char* SpriteSet::GetQuadData(const size_t frameIndex) { return _sprites[frameIndex]->GetQuadData(0); }
