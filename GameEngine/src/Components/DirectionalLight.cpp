#include "GameEngine/Components/DirectionalLight.h"

#include "imgui.h"
#include "GameEngine/Rendering/Light.h"
#include "glm/gtc/type_ptr.hpp"

using namespace GameEngine::Components;

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
    

    Light::AddDirectionalLight(_eulerAngles, _color, _intensity);
}
