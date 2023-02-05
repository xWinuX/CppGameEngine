#include "GameEngine/Rendering/Light.h"

#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;

Light::UniformBufferData* Light::_lightData          = new Light::UniformBufferData();
UniformBuffer*    Light::_lightUniformBuffer = nullptr;

void Light::Initialize()
{
    _lightUniformBuffer = new UniformBuffer(reinterpret_cast<const unsigned char*>(_lightData), sizeof(Light::UniformBufferData), 1, GL_DYNAMIC_DRAW);
    _lightUniformBuffer->Bind(2);
}


void Light::Update()
{
    _lightUniformBuffer->UpdateData(reinterpret_cast<const unsigned char*>(_lightData), 1);

    _lightData->NumDirectionalLights = 0;
    _lightData->NumPointLights       = 0;
}

void Light::AddPointLight(const glm::vec3 position, const glm::vec4 color, const float intensity, const float ranges)
{
    const int num = _lightData->NumPointLights;
    if (num >= MaxPointLights)
    {
        Debug::Log::Message("Too many point lights!");
        return;
    }

    _lightData->PointLightPositions[num]     = glm::vec4(position, 0.0);
    _lightData->PointLightColors[num]        = color;
    _lightData->PointLightIntensities[num].x = intensity;
    _lightData->PointLightRanges[num].x      = ranges;

    _lightData->NumPointLights++;
}

void Light::AddDirectionalLight(const glm::vec3 direction, const glm::vec4 color, const float intensity)
{
    const int num = _lightData->NumDirectionalLights;
    if (num >= MaxDirectionalLights)
    {
        Debug::Log::Message("Too many directional lights!");
        return;
    }

    _lightData->DirectionalLightDirections[num]    = glm::vec4(direction, 0.0);
    _lightData->DirectionalLightColors[num]        = color;
    _lightData->DirectionalLightIntensities[num].x = intensity;

    _lightData->NumDirectionalLights++;
}
