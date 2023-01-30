#include "GameEngine/Components/SpriteRenderer.h"

#include <glm/gtx/integer.hpp>

#include "GameEngine/Components/Transform.h"
#include "GameEngine/Rendering/Renderer.h"
#include "GameEngine/Rendering/Sprite.h"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;

SpriteRenderer::SpriteRenderer(Rendering::RenderableSprite* sprite, Rendering::Material* material):
    _sprite(sprite),
    _material(material) {}

void SpriteRenderer::OnUpdateEnd() { Renderer::SubmitBatchRenderable2D(this); }

void SpriteRenderer::OnUpdate() { _frameIndex = fmod(_frameIndex + Time::GetDeltaTime() * _framesPerSecond, static_cast<float>(_sprite->GetNumFrames())); }

size_t SpriteRenderer::GetCopySize() { return sizeof(Sprite::QuadData); }
size_t SpriteRenderer::GetQuadSize() { return sizeof(Sprite::QuadData); }

void SpriteRenderer::CopyQuadData(unsigned char* destination)
{
    const size_t frameIndex = static_cast<size_t>(floor(_frameIndex));
    memcpy(destination, _sprite->GetQuadDataWithTransform(frameIndex, _transform->GetTRS()), GetCopySize());
}

void SpriteRenderer::OnBeforeDraw() { _material->GetUniformStorage()->SetUniformInstant<glm::mat4>("u_Transform", _transform->GetTRS()); }

GameEngine::Rendering::Material* SpriteRenderer::GetMaterial() { return _material; }
GameEngine::Rendering::Texture*  SpriteRenderer::GetTexture() { return _sprite->GetTexture(static_cast<size_t>(floor(_frameIndex))); }

float SpriteRenderer::GetFrameIndex() const { return _frameIndex; }
void  SpriteRenderer::SetFrameIndex(const float frameIndex) { _frameIndex = frameIndex; }
void  SpriteRenderer::SetFramesPerSecond(const float framesPerSecond) { _framesPerSecond = framesPerSecond; }
void  SpriteRenderer::SetTransform(Components::Transform* transform) { _transform = transform; }
void  SpriteRenderer::SetSprite(Rendering::RenderableSprite* sprite)
{
    _sprite = sprite;
    _frameIndex = fmod(_frameIndex, static_cast<float>(_sprite->GetNumFrames()));
}
