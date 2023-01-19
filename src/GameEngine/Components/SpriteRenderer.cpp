#include "SpriteRenderer.h"
#include "Transform.h"
#include "../Rendering/Renderer.h"
#include "../Utils/Math.h"
#include "../Utils/Time.h"
#include "glm/gtx/integer.hpp"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;
using namespace GameEngine::Utils;

SpriteRenderer::SpriteRenderer(Rendering::Sprite* sprite, Rendering::Material* material):
    _sprite(sprite),
    _material(material) {}

void SpriteRenderer::OnBeforeRender()
{
    for (unsigned int i = 0; i < 5000; i++)
    {
        Renderer::SubmitRenderable2D(this);
    }
}

void SpriteRenderer::OnUpdate() { _frameIndex = fmod(_frameIndex + Time::GetDeltaTime() * _framesPerSecond, static_cast<float>(_sprite->GetNumFrames())); }

unsigned SpriteRenderer::GetQuadSize() { return sizeof(Sprite::QuadData); }

void SpriteRenderer::CopyQuadData(unsigned char* destination) { memcpy(destination, _sprite->GetQuadData(static_cast<unsigned int>(floor(_frameIndex))), GetQuadSize()); }

void SpriteRenderer::OnBeforeDraw() { _material->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_Transform", _transform->GetTRS()); }

GameEngine::Rendering::Material* SpriteRenderer::GetMaterial() { return _material; }
GameEngine::Rendering::Texture*  SpriteRenderer::GetTexture() { return _sprite->GetTextures()[0]; }

float SpriteRenderer::GetFrameIndex() const { return _frameIndex; }
void  SpriteRenderer::SetFrameIndex(const float frameIndex) { _frameIndex = frameIndex; }
void  SpriteRenderer::SetFramesPerSecond(const float framesPerSecond) { _framesPerSecond = framesPerSecond; }
void  SpriteRenderer::SetTransform(Components::Transform* transform) { _transform = transform; }
