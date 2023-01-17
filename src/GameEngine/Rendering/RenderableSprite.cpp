#include "RenderableSprite.h"

GameEngine::Rendering::RenderableSprite::RenderableSprite(Sprite* sprite, Material* material):
    _sprite(sprite),
    _material(material) {}

unsigned GameEngine::Rendering::RenderableSprite::GetVertexSize() { return sizeof(Sprite::VertexData); }

void GameEngine::Rendering::RenderableSprite::CopyQuadData(unsigned char* destination, const unsigned frameIndex, const unsigned numQuads)
{
    memcpy(destination, _sprite->GetQuadData(frameIndex), GetVertexSize() * numQuads * 4);
}
