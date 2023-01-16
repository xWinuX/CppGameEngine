#include "Sprite.h"

#include "glm/gtc/constants.hpp"

using namespace GameEngine::Rendering;

void Sprite::AddSpriteQuad(const float aspectRatio, const glm::vec2 uvStep = glm::one<glm::vec2>(), const glm::ivec2 offset = glm::zero<glm::vec2>())
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
}

Sprite::Sprite(Texture* texture):
    _texture(texture),
    _frameSize(texture->GetSize()) { AddSpriteQuad(_frameSize.x / _frameSize.y); }

Sprite::Sprite(Texture* texture, const unsigned int numFrames, const glm::vec2 frameSize):
    _texture(texture),
    _frameSize(frameSize),
    _numFrames(numFrames)
{
    const float aspectRatio = _frameSize.x / _frameSize.y;
    const float uStep       = 1.0f / static_cast<float>(numFrames);
    for (unsigned int i = 0; i < _numFrames; i++) { AddSpriteQuad(aspectRatio, {uStep, 1.0}, {i, 0}); }
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

VertexArrayObject* Sprite::GetVertexArrayObject() const { return _vertexArrayObject; }
Texture*           Sprite::GetTexture() const { return _texture; }
unsigned           Sprite::GetNumFrames() const { return _numFrames; }
