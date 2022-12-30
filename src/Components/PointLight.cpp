#include "PointLight.h"

std::vector<glm::vec3> PointLight::_positions = std::vector<glm::vec3>();
std::vector<glm::vec4> PointLight::_colors    = std::vector<glm::vec4>();

void PointLight::OnBeforeRender()
{
    _positions.push_back(_transform->GetPosition());
    _colors.emplace_back(_color);
    Light::OnBeforeRender();
}

void PointLight::OnShaderUse()
{
    _shader->SetUniformInstant<int>("u_NumPointLights", static_cast<int>(_positions.size()));
    _shader->SetUniformInstant<std::vector<glm::vec3>*>("u_PointLightPositions", &_positions);
    _shader->SetUniformInstant<std::vector<glm::vec4>*>("u_PointLightColors", &_colors);
}

void PointLight::SetColor(const glm::vec4 color) { _color = color; }

void PointLight::OnFrameEnd()
{
    _positions.clear();
    _colors.clear();
}
