#include "SpriteRenderer.h"
#include "Transform.h"
#include "../Rendering/Renderer.h"
#include "../Utils/Time.h"
#include "glm/gtx/integer.hpp"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;

SpriteRenderer::SpriteRenderer(Rendering::Sprite* sprite, Rendering::Material* material):
    _sprite(sprite),
    _material(material),
    _renderableSprite(new RenderableSprite(sprite, material)) {}

void SpriteRenderer::OnBeforeRender() { Renderer::SubmitRenderable2D(_renderableSprite); }

void SpriteRenderer::OnUpdate()
{
    _animationTimer = fmod(_animationTimer + Time::GetDeltaTime(), static_cast<float>(_sprite->GetNumFrames()));
    Debug::Log::Message(std::to_string(_animationTimer));
}
