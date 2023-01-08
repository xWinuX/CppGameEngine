﻿#include "PointLight.h"

using namespace GameEngine::Components;

std::vector<glm::vec3> PointLight::_positions   = std::vector<glm::vec3>();
std::vector<glm::vec4> PointLight::_colors      = std::vector<glm::vec4>();
std::vector<float>     PointLight::_intensities = std::vector<float>();
std::vector<float>     PointLight::_ranges      = std::vector<float>();

void PointLight::SetColor(const glm::vec4 color) { _color = color; }
void PointLight::SetRange(const float range) { _range = range; }
void PointLight::SetIntensity(const float intensity) { _intensity = intensity; }

void PointLight::OnBeforeRender()
{
    _positions.push_back(_transform->GetPosition());
    _colors.emplace_back(_color);
    _intensities.push_back(_intensity);
    _ranges.push_back(_range);
    Light::OnBeforeRender();
}

void PointLight::OnShaderUse()
{
    _shader->SetUniformInstant<int>("u_NumPointLights", static_cast<int>(_positions.size()));
    _shader->SetUniformInstant<std::vector<glm::vec3>*>("u_PointLightPositions", &_positions);
    _shader->SetUniformInstant<std::vector<glm::vec4>*>("u_PointLightColors", &_colors);
    _shader->SetUniformInstant<std::vector<float>*>("u_PointLightIntensities", &_intensities);
    _shader->SetUniformInstant<std::vector<float>*>("u_PointLightRanges", &_ranges);
}

void PointLight::OnFrameEnd()
{
    _positions.clear();
    _colors.clear();
    _intensities.clear();
    _ranges.clear();
}