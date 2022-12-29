#include "PointLight.h"

std::vector<glm::vec3> PointLight::_positions = std::vector<glm::vec3>();
 
void PointLight::OnShaderUse()
{
    _shader->SetUniformInstant<int>("u_NumPointLights", static_cast<int>(_positions.size()));
    _shader->SetUniformInstant<std::vector<glm::vec3>*>("u_PointLightPositions", &_positions);
}
