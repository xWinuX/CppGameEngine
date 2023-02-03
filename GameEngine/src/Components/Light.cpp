#include "GameEngine/Components/Light.h"

#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;


void Light::OnUpdateBegin() { _alreadySubmitted = false; }

void Light::OnUpdateEnd()
{
    if (_alreadySubmitted) { return; }
    Renderer::SubmitLight(this);
    _alreadySubmitted = true;
}
