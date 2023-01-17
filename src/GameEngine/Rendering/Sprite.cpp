#include "Sprite.h"

#include "glm/gtc/constants.hpp"

using namespace GameEngine::Rendering;

void Sprite::AddSpriteQuad(const float aspectRatio, const glm::vec2 uvStep = glm::one<glm::vec2>(), const glm::uvec2 offset = glm::zero<glm::uvec2>())
{
    float uStepBegin = uvStep.x * static_cast<float>(offset.x);
    float uStepEnd   = uvStep.x * static_cast<float>(offset.x + 1);
    float vStepBegin = uvStep.y * static_cast<float>(offset.y);
    float vStepEnd   = uvStep.y * static_cast<float>(offset.y + 1);

    unsigned int indicesOffset = _vertexData.size();

    _indices.insert(_indices.end(), {indicesOffset + 2, indicesOffset + 1, indicesOffset, indicesOffset + 1, indicesOffset + 2, indicesOffset + 3});

    // vertexData
    Debug::Log::Message(std::to_string(uStepBegin));
    Debug::Log::Message(std::to_string(uStepEnd));
    Debug::Log::Message(std::to_string(vStepBegin));
    Debug::Log::Message(std::to_string(vStepEnd));
    Debug::Log::Message(std::to_string(offset.x));
    Debug::Log::Message(std::to_string(offset.y));
    _vertexData.insert(
                       _vertexData.end(),
                       {
                           {0, aspectRatio, {uStepBegin, vStepEnd}, glm::vec4(1.0)},
                           {1, aspectRatio, {uStepEnd, vStepEnd}, glm::vec4(1.0)},
                           {2, aspectRatio, {uStepBegin, vStepBegin}, glm::vec4(1.0)},
                           {3, aspectRatio, {uStepEnd, vStepBegin}, glm::vec4(1.0)}
                       });

    _framePositions.emplace_back(offset.x * _frameSize.x, offset.y * _frameSize.y);
}

Sprite::Sprite(Texture* texture):
    _sourceTexture(texture),
    _frameSize(texture->GetSize())
{
    AddSpriteQuad(static_cast<float>(_frameSize.x) / static_cast<float>(_frameSize.y));
    _textures.push_back(texture);
}

Sprite::Sprite(Texture* texture, const unsigned int numFrames, const glm::uvec2 frameSize):
    _sourceTexture(texture),
    _frameSize(frameSize),
    _numFrames(numFrames)
{
    const float aspectRatio = static_cast<float>(_frameSize.x) / static_cast<float>(_frameSize.y);
    const float uStep       = 1.0f / static_cast<float>(numFrames);
    for (unsigned int i = 0; i < _numFrames; i++)
    {
        AddSpriteQuad(aspectRatio, {uStep, 1.0}, {i, 0});
        _textures.push_back(texture);
    }
}

void Sprite::Finalize()
{
    VertexBuffer*       vertexBuffer       = new VertexBuffer(reinterpret_cast<unsigned char*>(_vertexData.data()), sizeof(Sprite::VertexData), _vertexData.size());
    IndexBuffer*        indexBuffer        = new IndexBuffer(reinterpret_cast<unsigned char*>(_indices.data()), sizeof(unsigned int), _indices.size());
    VertexBufferLayout* vertexBufferLayout = new VertexBufferLayout(new VertexBufferAttribute[4]
                                                                    {
                                                                        VertexBufferAttribute(1, GL_FLOAT, GL_FALSE, sizeof(Sprite::VertexData), nullptr),
                                                                        VertexBufferAttribute(1, GL_FLOAT, GL_FALSE, sizeof(Sprite::VertexData), (GLvoid*)(1 * sizeof(float))),
                                                                        VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Sprite::VertexData), (GLvoid*)(2 * sizeof(float))),
                                                                        VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::VertexData), (GLvoid*)(4 * sizeof(float))),
                                                                    }, 4);

    _vertexArrayObject = new VertexArrayObject(vertexBuffer, indexBuffer, vertexBufferLayout);
}

void Sprite::ChangeFrameUV(const unsigned int frameIndex, const glm::vec2 topLeftUV, const glm::vec2 bottomRightUV)
{
    _vertexData[(frameIndex * 4)].UV     = topLeftUV;
    _vertexData[(frameIndex * 4) + 1].UV = {topLeftUV.x, bottomRightUV.y};
    _vertexData[(frameIndex * 4) + 2].UV = {bottomRightUV.x, bottomRightUV.y};
    _vertexData[(frameIndex * 4) + 3].UV = {bottomRightUV.x, bottomRightUV.y};
}

void Sprite::ChangeFrameTexture(const unsigned frameIndex, Texture* texture) { _textures[frameIndex] = texture; }

unsigned char* Sprite::GetQuadData(const unsigned frameIndex) { return reinterpret_cast<unsigned char*>(_vertexData.data() + frameIndex); }
Texture*       Sprite::GetSourceTexture() const { return _sourceTexture; }


VertexArrayObject*             Sprite::GetVertexArrayObject() const { return _vertexArrayObject; }
const std::vector<Texture*>&   Sprite::GetTextures() const { return _textures; }
unsigned int                   Sprite::GetNumFrames() const { return _numFrames; }
glm::uvec2                     Sprite::GetFrameSize() const { return _frameSize; }
const std::vector<glm::uvec2>& Sprite::GetFramePositions() { return _framePositions; }
