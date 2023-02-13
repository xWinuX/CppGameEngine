#include "GameEngine/Rendering/Renderable.h"

void GameEngine::Rendering::Renderable::OnBeforeDraw() {}
void GameEngine::Rendering::Renderable::OnDraw() {}

void              GameEngine::Rendering::Renderable::SetLayer(const Layer layer) { _layer = layer; }
GameEngine::Layer GameEngine::Rendering::Renderable::GetLayer() const { return _layer; }
