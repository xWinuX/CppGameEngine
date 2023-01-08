#include "Light.h"

#include "../Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;

Light::Light(Shader* shader):
    _shader(shader) {}

void Light::OnBeforeRender() { Renderer::SubmitLight(this); }
