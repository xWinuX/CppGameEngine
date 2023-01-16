#include "SpriteRenderer.h"
#include "Transform.h"
#include "../Rendering/Renderer.h"
#include "../Utils/Time.h"
#include "glm/gtx/integer.hpp"

GameEngine::Components::SpriteRenderer::SpriteRenderer(Rendering::Sprite* sprite, Rendering::Material* material):
    _sprite(sprite),
    _material(material) {}

void GameEngine::Components::SpriteRenderer::OnBeforeDraw()
{
    if (_transform == nullptr) { return; }
    
    _material->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_Transform", _transform->GetTRS());
}

void GameEngine::Components::SpriteRenderer::OnDraw()
{
    _sprite->GetVertexArrayObject()->Bind();
    _sprite->GetVertexArrayObject()->Render(6, 6*floor(_animationTimer));
    _sprite->GetVertexArrayObject()->Unbind();
}

void GameEngine::Components::SpriteRenderer::OnBeforeRender()
{
    Rendering::Renderer::SubmitRenderable(this);
}

void GameEngine::Components::SpriteRenderer::OnUpdate()
{
    _animationTimer = fmod(_animationTimer + Time::GetDeltaTime(), static_cast<float>(_sprite->GetNumFrames()));
    Debug::Log::Message(std::to_string(_animationTimer));
}

GameEngine::Rendering::Material* GameEngine::Components::SpriteRenderer::GetMaterial() { return _material; }
