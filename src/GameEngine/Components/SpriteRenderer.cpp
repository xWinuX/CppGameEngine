#include "SpriteRenderer.h"
#include "Transform.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Sprite.h"
#include "../Utils/Math.h"
#include "../Utils/Time.h"
#include "glm/gtx/integer.hpp"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;
using namespace GameEngine::Utils;

SpriteRenderer::SpriteRenderer(Rendering::RenderableSprite* sprite, Rendering::Material* material):
    _sprite(sprite),
    _material(material) {}

void SpriteRenderer::OnBeforeRender() { Renderer::SubmitRenderable2D(this); }

void SpriteRenderer::OnUpdate() { _frameIndex = fmod(_frameIndex + Time::GetDeltaTime() * _framesPerSecond, static_cast<float>(_sprite->GetNumFrames())); }

unsigned SpriteRenderer::GetQuadSize() { return sizeof(Sprite::QuadData); }

void SpriteRenderer::CopyQuadData(unsigned char* destination)
{
    const size_t frameIndex = static_cast<size_t>(floor(_frameIndex));
    memcpy(destination, _sprite->GetQuadData(frameIndex, _transform->GetTRS()), GetQuadSize());
}

void SpriteRenderer::OnBeforeDraw() { _material->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_Transform", _transform->GetTRS()); }

GameEngine::Rendering::Material* SpriteRenderer::GetMaterial() { return _material; }
GameEngine::Rendering::Texture*  SpriteRenderer::GetTexture() { return _sprite->GetTexture(static_cast<size_t>(floor(_frameIndex))); }

float SpriteRenderer::GetFrameIndex() const { return _frameIndex; }
void  SpriteRenderer::SetFrameIndex(const float frameIndex) { _frameIndex = frameIndex; }
void  SpriteRenderer::SetFramesPerSecond(const float framesPerSecond) { _framesPerSecond = framesPerSecond; }
void  SpriteRenderer::SetTransform(Components::Transform* transform) { _transform = transform; }
