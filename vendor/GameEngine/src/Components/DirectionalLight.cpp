#include "GameEngine/Components/DirectionalLight.h"

#include "imgui.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/Rendering/Light.h"
#include "GameEngine/Rendering/Renderer.h"
#include "glm/gtc/type_ptr.hpp"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;

DirectionalLight::DirectionalLight(const bool isShadowCaster, const glm::vec4 color, const float intensity):
    Component("Directional Light"),
    _isShadowCaster(isShadowCaster),
    _color(color),
    _intensity(intensity) { }

void DirectionalLight::SetColor(const glm::vec4 color) { _color = color; }
void DirectionalLight::SetIntensity(const float intensity) { _intensity = intensity; }

void DirectionalLight::OnUpdate()
{
    ImGui::ColorPicker4("Directional Light Color", glm::value_ptr(_color));
    ImGui::SliderFloat("Directional Light Intensity", &_intensity, 0.0f, 10.0f);
    ImGui::SliderFloat3("Directional Light Rotation", glm::value_ptr(_eulerAngles), 0.0f, 6.0f);


    _transform->SetRotation(glm::quat(_eulerAngles));
    Light::AddDirectionalLight(_transform->GetForward(), _color, _intensity);
}

void DirectionalLight::OnUpdateEnd() { if (_isShadowCaster) { Light::SetDirectionalShadowCaster(_transform->GetForward(), _cascadeFactors); } }
