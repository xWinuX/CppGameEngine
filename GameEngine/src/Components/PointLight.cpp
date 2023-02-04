﻿#include "GameEngine/Components/PointLight.h"

#include <imgui.h>

#include "GameEngine/Components/Transform.h"

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
    _positions.push_back(_transform->GetPosition());
    _colors.emplace_back(_color);
    _intensities.push_back(_intensity);
    _ranges.push_back(_range);
    Light::OnUpdateEnd();
}

void PointLight::OnShaderUse(Rendering::Shader* shader)
{
    shader->SetUniformInstantly<int>("u_NumPointLights", static_cast<int>(_positions.size()));
    //shader->SetUniformArrayInstantly<glm::vec3>("u_PointLightPositions", _positions);
    //shader->SetUniformArrayInstantly<glm::vec4>("u_PointLightColors", _colors);
    //shader->SetUniformArrayInstantly<float>("u_PointLightIntensities", _intensities);
    //shader->SetUniformArrayInstantly<float>("u_PointLightRanges", _ranges);
}


void PointLight::OnFrameEnd()
{
    _positions.clear();
    _colors.clear();
    _intensities.clear();
    _ranges.clear();
}
