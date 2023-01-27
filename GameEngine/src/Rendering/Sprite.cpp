#include "GameEngine/Rendering/Sprite.h"

#include <glm/ext/matrix_transform.hpp>

using namespace GameEngine::Rendering;

Sprite::Sprite(Texture* texture, const unsigned int pixelsPerUnit):
    _sourceTexture(texture),
    _texture(texture),
    _pixelPosition(glm::uvec2(0, 0)),
    _size(texture->GetSize()),
    _pixelsPerUnit(pixelsPerUnit),
    _pixelsPerUnitFactor(1.0f / static_cast<float>(pixelsPerUnit)) { CreateSpriteQuad(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)); }

Sprite::Sprite(Texture* texture, const glm::uvec2 pixelPosition, const glm::uvec2 size, const glm::vec2 uvTopLeft, const glm::vec2 uvBottomRight, const unsigned int pixelsPerUnit):
    _sourceTexture(texture),
    _texture(texture),
    _pixelPosition(pixelPosition),
    _size(size),
    _pixelsPerUnit(pixelsPerUnit),
    _pixelsPerUnitFactor(1.0f / static_cast<float>(pixelsPerUnit)) { CreateSpriteQuad(uvTopLeft, uvBottomRight); }

Sprite::Sprite(Texture* texture, const glm::uvec2 pixelPosition, const glm::vec4 posLRTB, const glm::vec2 uvTopLeft, const glm::vec2 uvBottomRight, const unsigned pixelsPerUnit):
    _sourceTexture(texture),
    _texture(texture),
    _pixelPosition(pixelPosition),
    _size(glm::vec2(abs(posLRTB.x - posLRTB.y), abs(posLRTB.z - posLRTB.w))),
    _pixelsPerUnit(pixelsPerUnit),
    _pixelsPerUnitFactor(1.0f / static_cast<float>(pixelsPerUnit))
{
    _quadData = new QuadData{

        glm::identity<glm::mat4>(),

        glm::vec2(posLRTB.x, posLRTB.w),
        glm::vec2(uvTopLeft.x, uvBottomRight.y),

        glm::vec2(posLRTB.y, posLRTB.w),
        glm::vec2(uvBottomRight.x, uvBottomRight.y),

        glm::vec2(posLRTB.x, posLRTB.z),
        glm::vec2(uvTopLeft.x, uvTopLeft.y),

        glm::vec2(posLRTB.y, posLRTB.z),
        glm::vec2(uvBottomRight.x, uvTopLeft.y),

        {
            glm::one<glm::vec4>(),
            glm::one<glm::vec4>(),
            glm::one<glm::vec4>(),
            glm::one<glm::vec4>(),
        }
    };
}

Sprite::~Sprite() { delete _quadData; }

void Sprite::CreateSpriteQuad(const glm::vec2 uvTopLeft, const glm::vec2 uvBottomRight, const glm::vec2 origin)
{
    const glm::vec2 extends = static_cast<glm::vec2>(_size) * _pixelsPerUnitFactor;
    _quadData               = new QuadData{

        glm::identity<glm::mat4>(),

        glm::vec2(-extends.x, extends.y) * glm::vec2(origin.x, 1 - origin.y),
        glm::vec2(uvTopLeft.x, uvBottomRight.y),

        extends * (glm::one<glm::vec2>() - origin),
        glm::vec2(uvBottomRight.x, uvBottomRight.y),

        -extends * origin,
        glm::vec2(uvTopLeft.x, uvTopLeft.y),

        glm::vec2(extends.x, -extends.y) * glm::vec2(1 - origin.x, origin.y),
        glm::vec2(uvBottomRight.x, uvTopLeft.y),

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
    _quadData->UV0 = topLeftUV;
    _quadData->UV1 = {bottomRightUV.x, topLeftUV.y};
    _quadData->UV2 = {topLeftUV.x, bottomRightUV.y};
    _quadData->UV3 = bottomRightUV;
}

void              Sprite::SetTexture(Texture* texture) { _texture = texture; }
void              Sprite::SetTrs(const glm::mat4 trs) const { _quadData->Transform = trs; }
size_t            Sprite::GetNumFrames() { return 1; }
Sprite::QuadData* Sprite::GetQuadDataPtr() const { return _quadData; }

unsigned char* Sprite::GetQuadDataWithTransform(const size_t frameIndex, const glm::mat4 transform)
{
    SetTrs(transform);
    return reinterpret_cast<unsigned char*>(_quadData);
}

unsigned char* Sprite::GetQuadData(const size_t frameIndex) { return reinterpret_cast<unsigned char*>(_quadData); }

Texture* Sprite::GetTexture(const size_t frameIndex) { return _texture; }
float    Sprite::GetPixelsPerUnitFactor() const { return _pixelsPerUnitFactor; }


Texture*   Sprite::GetSourceTexture() const { return _sourceTexture; }
glm::vec2  Sprite::GetPixelPosition() const { return _pixelPosition; }
glm::uvec2 Sprite::GetSize() const { return _size; }
