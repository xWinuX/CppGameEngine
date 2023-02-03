#include "DirectionalLight.h"

#include "imgui.h"
#include "GameEngine/Components/Transform.h"

std::vector<glm::vec3> DirectionalLight::_directions  = std::vector<glm::vec3>();
std::vector<glm::vec4> DirectionalLight::_colors      = std::vector<glm::vec4>();
std::vector<float>     DirectionalLight::_intensities = std::vector<float>();

DirectionalLight::DirectionalLight(const glm::vec4 color, const float intensity):
    _color(color),
    _intensity(intensity) {}

void DirectionalLight::SetColor(const glm::vec4 color) { _color = color; }
void DirectionalLight::SetIntensity(const float intensity) { _intensity = intensity; }

void DirectionalLight::OnUpdateEnd()
{
    ImGui::ColorPicker4("Directional Light Color", glm::value_ptr(_color));
    ImGui::SliderFloat("Directional Light Intensity", &_intensity, 0.0f, 10.0f);
    ImGui::SliderFloat3("Directional Light Rotation", glm::value_ptr(_eulerAngles), 0.0f, 6.0f);

    _transform->SetRotation(glm::quat(_eulerAngles));
    _directions.emplace_back(_transform->GetForward());
    _colors.emplace_back(_color);
    _intensities.push_back(_intensity);

    Light::OnUpdateEnd();
}

void DirectionalLight::OnShaderUse(GameEngine::Rendering::Shader* shader)
{
    //shader->SetUniformInstant<int>("u_NumDirectionalLights", static_cast<int>(_directions.size()));
    //shader->SetUniformInstant<std::vector<glm::vec3>>("u_DirectionalLightDirections", _directions);
    //shader->SetUniformInstant<std::vector<glm::vec4>>("u_DirectionalLightColors", _colors);
    //shader->SetUniformInstant<std::vector<float>>("u_DirectionalLightIntensities", _intensities);
}

void DirectionalLight::OnFrameEnd()
{
    _directions.clear();
    _colors.clear();
    _intensities.clear();
}
