#include "Sprite.h"

#include "glm/gtc/constants.hpp"


GameEngine::Rendering::Sprite::VertexData* GameEngine::Rendering::Sprite::CreateSpriteQuad(const float      aspectRatio, const glm::vec2 uvStep = glm::one<glm::vec2>(),
                                                                                           const glm::ivec2 offset                              = glm::one<glm::vec2>())
{
    float uStepBegin = uvStep.x * static_cast<float>(offset.x);
    float uStepEnd   = uvStep.x * static_cast<float>(offset.x + 1u);
    float vStepBegin = uvStep.y * static_cast<float>(offset.y);
    float vStepEnd   = uvStep.y * static_cast<float>(offset.y + 1u);
    return new VertexData[4]
    {
        {
            aspectRatio,
            {uStepBegin, vStepBegin},
            glm::vec4(1.0)
        },
        {
            aspectRatio,
            {uStepEnd, vStepBegin},
            glm::vec4(1.0)
        },
        {
            aspectRatio,
            {uStepBegin, vStepEnd},
            glm::vec4(1.0)
        },
        {
            aspectRatio,
            {uStepEnd, vStepEnd},
            glm::vec4(1.0)
        },
    };
}

GameEngine::Rendering::Sprite::Sprite(Texture* texture):
    _texture(texture),
    _frameSize(texture->GetSize()) { _vertexData.push_back(CreateSpriteQuad(_frameSize.x / _frameSize.y)); }

GameEngine::Rendering::Sprite::Sprite(Texture* texture, const unsigned int numFrames, const glm::vec2 frameSize):
    _texture(texture),
    _frameSize(frameSize),
    _numFrames(numFrames)
{
    const float aspectRatio = _frameSize.x / _frameSize.y;
    const float uStep       = 1.0f / static_cast<float>(texture->GetSize().x);
    for (unsigned int i = 0; i < _numFrames; i++)
    {
        float stepBegin = uStep * static_cast<float>(i);
        float stepEnd   = uStep * static_cast<float>(i + 1u);
        _vertexData.push_back(CreateSpriteQuad(aspectRatio, {uStep, 1.0}, {i, 0}));
    }
}

void GameEngine::Rendering::Sprite::Finalize()
{
    _vertexArrayObject
}
