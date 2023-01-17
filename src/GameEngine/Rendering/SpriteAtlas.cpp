#include "SpriteAtlas.h"

#include <algorithm>

#include "stb_image_write.h"
#include "glm/gtx/string_cast.hpp"

using namespace GameEngine::Rendering;

GameEngine::Rendering::SpriteAtlas::SpriteAtlas(const glm::uvec2 size):
    _size(size),
    _uvStep(glm::vec2(1 / _size.x, 1 / _size.y)) {}

void SpriteAtlas::ExportPages() const
{
    for (unsigned int i = 0; i < _buffers.size(); i++)
    {
        std::string fileName = "test_image" + std::to_string(i) + ".png";
        stbi_write_png(fileName.c_str(), static_cast<int>(_size.x), static_cast<int>(_size.y), 4, _buffers[i], static_cast<int>(_size.x) * 4);
    }
}

void GameEngine::Rendering::SpriteAtlas::AddSprite(Sprite* sprite) { _sprites.push_back({sprite, 0, false}); }

void SpriteAtlas::CreateNewPage()
{
    Debug::Log::Message("Create new page");
    _buffers.push_back(new unsigned char[_size.x * _size.y * 4]);
    memset(_buffers[_buffers.size() - 1], 0, _size.x * _size.y * 4);
}

// Simple Packing algorithm: https://www.david-colson.com/2020/03/10/exploring-rect-packing.html
void SpriteAtlas::Pack()
{
    // Sort sprites based on height
    std::sort(_sprites.begin(), _sprites.end(),
              [](const PackingSprite sprite1, const PackingSprite sprite2) { return sprite1.Sprite->GetTexture()->GetSize().y > sprite2.Sprite->GetTexture()->GetSize().y; });

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

            Sprite*          sprite        = packingSprite.Sprite;
            const Texture*   spriteTexture = sprite->GetTexture();
            const glm::uvec2 frameSize     = sprite->GetFrameSize();
            const glm::vec2  frameUVStep   = glm::vec2(_uvStep.x * static_cast<float>(frameSize.x), _uvStep.y * static_cast<float>(frameSize.y));
            // Loop trough each individual frame of sprite
            for (unsigned int frameIndex = packingSprite.PackedFrames; frameIndex < sprite->GetNumFrames(); frameIndex++)
            {
                const glm::uvec2 framePosition = sprite->GetFramePositions()[frameIndex];

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
                    memcpy(_buffers[_buffers.size() - 1] + bufferRowOffset, spriteBuffer + xOffset + yOffset, frameSize.x * 4);
                    bufferRowOffset += _size.x * 4;
                }

                // Update sprite uvs
                glm::vec2 topLeftUV = glm::vec2(static_cast<float>(position.x) * _uvStep.x, static_cast<float>(position.y) * _uvStep.y);
                sprite->ChangeFrameUV(frameIndex, topLeftUV, topLeftUV + frameUVStep);

                // Update cursor x position to end of currently inserted sprite 
                position.x += frameSize.x;

                // Update largest height if needed 
                if (frameSize.y > largestHeightInCurrentRow) { largestHeightInCurrentRow = frameSize.y; }

                // If every sprite frame has been packed mark sprite as packed
                packingSprite.PackedFrames++;
                if (packingSprite.PackedFrames == sprite->GetNumFrames())
                {
                    packingSprite.WasPacked = true;
                    numPackedSprites++;
                }
            }
        }
    }

    for (unsigned char* buffer : _buffers) { _pages.push_back(new Texture(buffer, _size)); }
    _buffers.clear();

    ExportPages();
}
