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

void DirectionalLight::OnUpdate() { Light::AddDirectionalLight(_transform->GetForward(), _color, _intensity); }

void DirectionalLight::OnUpdateEnd() { if (_isShadowCaster) { Light::SetDirectionalShadowCaster(_transform->GetForward(), _cascadeFactors); } }

void DirectionalLight::OnGuiDraw()
{
    ImGui::InputFloat(GetImGuiIDString("Intensity").c_str(), &_intensity);
    ImGui::ColorPicker4(GetImGuiIDString("Color").c_str(), glm::value_ptr(_color));
}
