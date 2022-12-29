#include "Light.h"

#include "../Rendering/Renderer.h"

Light::Light(Shader* shader):
    _shader(shader) {}

void Light::OnBeforeRender() { Renderer::SubmitLight(this); }
