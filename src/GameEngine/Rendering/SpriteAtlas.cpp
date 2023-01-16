#include "SpriteAtlas.h"

#include "stb_image_write.h"

using namespace GameEngine::Rendering;

GameEngine::Rendering::SpriteAtlas::SpriteAtlas(const glm::uvec2 size):
    _size(size) { _buffer = new unsigned char[_size.x * _size.y * 4]; }

void SpriteAtlas::ExportImage() const { stbi_write_png("test_image.png", static_cast<int>(_size.x), static_cast<int>(_size.y), 4, _buffer, static_cast<int>(_size.x) * 4); }

void GameEngine::Rendering::SpriteAtlas::AddSprite(const Sprite* sprite)
{
    const Texture* texture = sprite->GetTexture();
    const unsigned char* spriteBuffer = texture->GetBuffer();
    unsigned int bufferRowOffset = _currentPosition.y * _size.x * 4 + _currentPosition.x * 4;
    for (unsigned int y = texture->GetSize().y; y > 0; y--) { // change this line
        memcpy(_buffer + bufferRowOffset, spriteBuffer + (y - 1) * texture->GetSize().x * 4, texture->GetSize().x * 4);
        bufferRowOffset += _size.x * 4;
    }
    _currentPosition.x += texture->GetSize().x;
    if (_currentPosition.x + texture->GetSize().x > _size.x) {
        _currentPosition.x = 0;
        _currentPosition.y += texture->GetSize().y;
    }
    ExportImage();
}
