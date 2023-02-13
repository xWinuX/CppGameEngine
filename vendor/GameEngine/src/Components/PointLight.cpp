#include "GameEngine/Components/PointLight.h"

#include <imgui.h>

#include "GameEngine/Components/Transform.h"
#include "GameEngine/Rendering/Light.h"

using namespace GameEngine::Components;

std::vector<glm::vec3> PointLight::_positions   = std::vector<glm::vec3>();
std::vector<glm::vec4> PointLight::_colors      = std::vector<glm::vec4>();
std::vector<float>     PointLight::_intensities = std::vector<float>();
std::vector<float>     PointLight::_ranges      = std::vector<float>();

PointLight::PointLight(const glm::vec4 color, const float range, const float intensity):
    _color(color),
    _range(range),
    _intensity(intensity) {}

void PointLight::SetColor(const glm::vec4 color) { _color = color; }
void PointLight::SetRange(const float range) { _range = range; }
void PointLight::SetIntensity(const float intensity) { _intensity = intensity; }

void PointLight::OnUpdateEnd()
{
    Light::AddPointLight(_transform->GetPosition(), _color, _intensity, _range);
}
