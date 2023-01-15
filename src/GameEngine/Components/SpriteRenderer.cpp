#include "SpriteRenderer.h"
#include "Transform.h"
#include "../Rendering/Renderer.h"

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
    _sprite->GetVertexArrayObject()->Render();
    _sprite->GetVertexArrayObject()->Unbind();
}

void GameEngine::Components::SpriteRenderer::OnBeforeRender()
{
    Rendering::Renderer::SubmitRenderable(this);
}

GameEngine::Rendering::Material* GameEngine::Components::SpriteRenderer::GetMaterial() { return _material; }
