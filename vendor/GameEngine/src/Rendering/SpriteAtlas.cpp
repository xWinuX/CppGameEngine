#include "GameEngine/Rendering/SpriteAtlas.h"

#include <algorithm>
#include <stb_image_write.h>
#include <glm/gtx/string_cast.hpp>

#include "GameEngine/Rendering/Sprite.h"

using namespace GameEngine::Rendering;

GameEngine::Rendering::SpriteAtlas::SpriteAtlas(const glm::uvec2 size, const TextureParams textureParams):
    _textureParams(textureParams),
    _size(size),
    _uvStep(glm::vec2(1.0f / static_cast<float>(size.x), 1.0f / static_cast<float>(size.y))) {}

void SpriteAtlas::ExportPages() const
{
    for (unsigned int i = 0; i < _buffers.size(); i++)
    {
        std::string fileName = "test_image" + std::to_string(i) + ".png";
        stbi_write_png(fileName.c_str(), static_cast<int>(_size.x), static_cast<int>(_size.y), 4, _buffers[i], static_cast<int>(_size.x) * 4);
    }
}

void GameEngine::Rendering::SpriteAtlas::AddSprite(SpriteSet* spriteSet) { for (size_t i = 0; i < spriteSet->GetNumFrames(); i++) { AddSprite(spriteSet->GetSprite(i)); } }
void SpriteAtlas::AddSprite(Sprite* sprite) { _sprites.push_back({sprite, false}); }

void SpriteAtlas::CreateNewPage()
{
    _buffers.push_back(new unsigned char[_size.x * _size.y * 4]);
    memset(_buffers[_buffers.size() - 1], 0, _size.x * _size.y * 4);
}

void SpriteAtlas::SortSpritesByHeight()
{
    std::sort(_sprites.begin(), _sprites.end(),
              [](const PackingSprite& sprite1, const PackingSprite& sprite2)
              {
                  return sprite1.Sprite->GetSourceTexture()->GetSize().y > sprite2.Sprite->GetSourceTexture()->GetSize().y;
              });
}

// Simple Packing algorithm: https://www.david-colson.com/2020/03/10/exploring-rect-packing.html
void SpriteAtlas::Pack()
{
    // Sort sprites based on height
    SortSpritesByHeight();

    // Loop for as long as there are sprites to pack
    unsigned int numPackedSprites = 0;
    while (numPackedSprites < _sprites.size())
    {
        // Create new atlas page
        CreateNewPage();

        // Loop trough each sprite 
        glm::uvec2   position                  = glm::zero<glm::uvec2>();
        unsigned int largestHeightInCurrentRow = 0;
        for (PackingSprite& packingSprite : _sprites)
        {
            // If sprite was already packed skip it
            if (packingSprite.WasPacked) { continue; }

            const Sprite*    sprite        = packingSprite.Sprite;
            const Texture2D*   spriteTexture = sprite->GetSourceTexture();
            const glm::uvec2 frameSize     = sprite->GetSize();
            const glm::vec2  frameUVStep   = glm::vec2(_uvStep.x * static_cast<float>(frameSize.x), _uvStep.y * static_cast<float>(frameSize.y));

            const glm::uvec2 framePosition = sprite->GetPixelPosition();

            // If sprite is too large to fit on current row reset cursor position back to the left and increase y position by the highest element in current row
            if (position.x + frameSize.x > _size.x)
            {
                position.y += largestHeightInCurrentRow;
                position.x                = 0;
                largestHeightInCurrentRow = 0;
            }

            // If the sprite is high to fit the page skip it
            if (position.y + frameSize.y > _size.y) { continue; }

            // Copy the contents of the texture into the atlas page
            const unsigned char* spriteBuffer    = spriteTexture->GetBuffer();
            unsigned int         bufferRowOffset = position.y * _size.x * 4 + position.x * 4;
            for (unsigned int y = frameSize.y; y > 0; y--) // Copy entire row at once
            {
                const unsigned int xOffset = framePosition.x * 4;
                const unsigned int yOffset = ((y - 1) + framePosition.y) * spriteTexture->GetSize().x * 4;
                memcpy(_buffers[_buffers.size() - 1] + bufferRowOffset, spriteBuffer + xOffset + yOffset, static_cast<size_t>(frameSize.x) * 4);
                bufferRowOffset += _size.x * 4;
            }

            // Update sprite uvs
            glm::vec2 topLeftUV = glm::vec2(static_cast<float>(position.x) * _uvStep.x, static_cast<float>(position.y) * _uvStep.y);
            sprite->SetUV(topLeftUV, topLeftUV + frameUVStep);

            // Update cursor x position to end of currently inserted sprite 
            position.x += frameSize.x;

            // Update largest height if needed 
            if (frameSize.y > largestHeightInCurrentRow) { largestHeightInCurrentRow = frameSize.y; }

            // Mark sprite as packed and give him the current page index
            packingSprite.PageIndex = _buffers.size() - 1;
            packingSprite.WasPacked = true;
            numPackedSprites++;
        }
    }

    ExportPages();

    // Create textures out of the buffers and clear the vector since the texture now manages the buffers memory
    for (unsigned char* buffer : _buffers) { _pages.push_back(new Texture2D(buffer, _size, _textureParams)); }

    for (const PackingSprite packingSprite : _sprites)
    {
        Sprite* sprite = packingSprite.Sprite;
        sprite->SetTexture(_pages[packingSprite.PageIndex]);
    }
    
    _buffers.clear();
}
