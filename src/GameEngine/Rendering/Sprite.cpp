#include "Sprite.h"

#include "glm/ext/matrix_transform.hpp"

using namespace GameEngine::Rendering;


Sprite::Sprite(Texture* texture):
    _sourceTexture(texture),
    _texture(texture),
    _pixelPosition(glm::uvec2(0, 0)),
    _size(texture->GetSize()) { CreateSpriteQuad(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)); }

Sprite::Sprite(Texture* texture, glm::uvec2 pixelPosition, const glm::uvec2 size, const glm::vec2 uvTopLeft, const glm::vec2 uvBottomRight):
    _sourceTexture(texture),
    _texture(texture),
    _pixelPosition(pixelPosition),
    _size(size) { CreateSpriteQuad(uvTopLeft, uvBottomRight); }

Sprite::~Sprite() { delete _quadData; }

void Sprite::CreateSpriteQuad(const glm::vec2 uvTopLeft, const glm::vec2 uvBottomRight)
{
    _quadData = new QuadData{

        glm::vec4(_size.x, _size.y, 0, 0),
        glm::identity<glm::mat4>(),
        {
            glm::vec2(uvTopLeft.x, uvBottomRight.y),
            glm::vec2(uvBottomRight.x, uvBottomRight.y),
            glm::vec2(uvTopLeft.x, uvTopLeft.y),
            glm::vec2(uvBottomRight.x, uvTopLeft.y),
        },
        {
            glm::one<glm::vec4>(),
            glm::one<glm::vec4>(),
            glm::one<glm::vec4>(),
            glm::one<glm::vec4>(),
        }
    };
}

void Sprite::SetUV(glm::vec2 topLeftUV, glm::vec2 bottomRightUV) const
{
    _quadData->UVs[0] = topLeftUV;
    _quadData->UVs[1] = {bottomRightUV.x, topLeftUV.y};
    _quadData->UVs[2] = {topLeftUV.x, bottomRightUV.y};
    _quadData->UVs[3] = bottomRightUV;
}

void   Sprite::SetTexture(Texture* texture) { _texture = texture; }
void   Sprite::SetTrs(const glm::mat4 trs) const { _quadData->Transform = trs; }
size_t Sprite::GetNumFrames() { return 1; }

unsigned char* Sprite::GetQuadData(const size_t frameIndex, const glm::mat4 transform)
{
    SetTrs(transform);
    return reinterpret_cast<unsigned char*>(_quadData);
}

Texture* Sprite::GetTexture(const size_t frameIndex) { return _texture; }


Texture*   Sprite::GetSourceTexture() const { return _sourceTexture; }
glm::vec2  Sprite::GetPixelPosition() const { return _pixelPosition; }
glm::uvec2 Sprite::GetSize() const { return _size; }
