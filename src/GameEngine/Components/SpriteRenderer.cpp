#include "SpriteRenderer.h"
#include "Transform.h"
#include "../Rendering/Renderer.h"
#include "glm/gtx/integer.hpp"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;

SpriteRenderer::SpriteRenderer(Rendering::Sprite* sprite, Rendering::Material* material):
    _material(material),
    _renderableSprite(new RenderableSprite(sprite, material)) {}

void SpriteRenderer::OnBeforeRender()
{
    Renderer::SubmitRenderable2D(_renderableSprite);
}

void SpriteRenderer::OnUpdate() { _renderableSprite->Update(); }

void SpriteRenderer::OnComponentAdded() { _renderableSprite->SetTransform(_transform); }
