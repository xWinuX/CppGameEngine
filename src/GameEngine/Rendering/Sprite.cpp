#include "Sprite.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/constants.hpp"

using namespace GameEngine::Rendering;

void Sprite::AddSpriteQuad(const float aspectRatio, const glm::vec2 uvStep = glm::one<glm::vec2>(), const glm::uvec2 offset = glm::zero<glm::uvec2>())
{
    const float uStepBegin = uvStep.x * static_cast<float>(offset.x);
    const float uStepEnd   = uvStep.x * static_cast<float>(offset.x + 1);
    const float vStepBegin = uvStep.y * static_cast<float>(offset.y);
    const float vStepEnd   = uvStep.y * static_cast<float>(offset.y + 1);

    unsigned int indicesOffset = static_cast<unsigned int>(_quadData.size());

    _indices.insert(_indices.end(), {indicesOffset + 2, indicesOffset + 1, indicesOffset, indicesOffset + 1, indicesOffset + 2, indicesOffset + 3});

    // vertexData
    _quadData.push_back({
                            aspectRatio,
                            glm::identity<glm::mat4>(),
                            {
                                glm::vec2(uStepBegin, vStepEnd),
                                glm::vec2(uStepEnd, vStepEnd),
                                glm::vec2(uStepBegin, vStepBegin),
                                glm::vec2(uStepEnd, vStepBegin),
                            },
                            {
                                glm::one<glm::vec4>(),
                                glm::one<glm::vec4>(),
                                glm::one<glm::vec4>(),
                                glm::one<glm::vec4>(),
                            }
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
    VertexBuffer*       vertexBuffer       = new VertexBuffer(reinterpret_cast<unsigned char*>(_quadData.data()), sizeof(Sprite::QuadData), _quadData.size());
    IndexBuffer*        indexBuffer        = new IndexBuffer(reinterpret_cast<unsigned char*>(_indices.data()), sizeof(unsigned int), _indices.size());
    VertexBufferLayout* vertexBufferLayout = new VertexBufferLayout(new VertexBufferAttribute[4]
                                                                    {
                                                                        VertexBufferAttribute(1, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), nullptr),
                                                                        VertexBufferAttribute(1, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(1 * sizeof(float))),
                                                                        VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(2 * sizeof(float))),
                                                                        VertexBufferAttribute(4, GL_FLOAT, GL_FALSE, sizeof(Sprite::QuadData), (GLvoid*)(4 * sizeof(float))),
                                                                    }, 4);

    _vertexArrayObject = new VertexArrayObject(vertexBuffer, indexBuffer, vertexBufferLayout);
}

void Sprite::ChangeFrameUV(const size_t frameIndex, const glm::vec2 topLeftUV, const glm::vec2 bottomRightUV)
{
    _quadData[frameIndex].UVs[0] = topLeftUV;
    _quadData[frameIndex].UVs[1] = {bottomRightUV.x, topLeftUV.y};
    _quadData[frameIndex].UVs[2] = {topLeftUV.x, bottomRightUV.y};
    _quadData[frameIndex].UVs[3] = bottomRightUV;
}

void Sprite::ChangeFrameTexture(const size_t frameIndex, Texture* texture) { _textures[frameIndex] = texture; }

void Sprite::SetQuadTransform(const size_t frameIndex, const glm::mat4 trs) { _quadData[frameIndex].Transform = trs; }

unsigned char* Sprite::GetQuadData(const size_t frameIndex) { return reinterpret_cast<unsigned char*>(_quadData.data() + frameIndex); }
Texture*       Sprite::GetSourceTexture() const { return _sourceTexture; }


VertexArrayObject*             Sprite::GetVertexArrayObject() const { return _vertexArrayObject; }
const std::vector<Texture*>&   Sprite::GetTextures() const { return _textures; }
unsigned int                   Sprite::GetNumFrames() const { return _numFrames; }
glm::uvec2                     Sprite::GetFrameSize() const { return _frameSize; }
const std::vector<glm::uvec2>& Sprite::GetFramePositions() { return _framePositions; }
