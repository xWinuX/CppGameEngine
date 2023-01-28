#include "GameEngine/Components/Light.h"

#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;

Light::Light(Shader* shader):
    _shader(shader) {}

void Light::OnUpdateEnd() { Renderer::SubmitLight(this); }
