#include "GameEngine/Rendering/Light.h"

#include "GameEngine/Components/Camera.h"
#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;

Light::UniformBufferData* Light::_lightData          = new Light::UniformBufferData();
CascadedShadowMap*        Light::_shadowMap          = nullptr;
UniformBuffer*            Light::_lightUniformBuffer = nullptr;
std::vector<glm::vec4>    Light::_frustumCorners     = std::vector<glm::vec4>(8);

void Light::Initialize()
{
    _shadowMap          = new CascadedShadowMap(glm::uvec2(4096));
    _lightUniformBuffer = new UniformBuffer(reinterpret_cast<unsigned char*>(_lightData), sizeof(Light::UniformBufferData), 1, GL_DYNAMIC_DRAW);
    _lightUniformBuffer->Bind(2);
}

void Light::Update()
{
    _lightUniformBuffer->UpdateData(reinterpret_cast<const unsigned char*>(_lightData), 1);

    _lightData->NumDirectionalLights = 0;
    _lightData->NumPointLights       = 0;
    _lightData->NumShadowCascades    = 0;

    Renderer::SetCascadedShadowMap(_shadowMap);
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
    const int numDirectionalLights = _lightData->NumDirectionalLights;
    if (numDirectionalLights >= MaxDirectionalLights)
    {
        Debug::Log::Message("Too many directional lights!");
        return;
    }

    _lightData->DirectionalLightDirections[numDirectionalLights]    = glm::vec4(direction, 0.0);
    _lightData->DirectionalLightColors[numDirectionalLights]        = color;
    _lightData->DirectionalLightIntensities[numDirectionalLights].x = intensity;

    _lightData->NumDirectionalLights++;
}


void Light::SetDirectionalShadowCaster(const glm::vec3 lightDirection, const std::array<float, 4> cascadeFactors, const float zMultiply)
{
    Camera* camera = Camera::GetMain();

    float nearPlane = camera->GetNearPlan();
    float farPlane  = camera->GetFarPlan();

    for (unsigned int i = 0; i < cascadeFactors.size() + 1; i++)
    {
        _frustumCorners.clear();

        // Create projection for each cascade
        glm::mat4 projection;
        if (i == 0) // If it is the first loop create are from near plane to first cascade
        {
            float cascade                                                      = farPlane * cascadeFactors[i];
            projection                                                         = camera->CreatePerspectiveProjection(nearPlane, cascade);
            _lightData->FrustumPlaneDistances[_lightData->NumShadowCascades].x = cascade;
        }
        else if (i < cascadeFactors.size()) // If it's not the first loop create cascade from last cascade to current cascade
        {
            float cascade                                                      = farPlane * cascadeFactors[i];
            projection                                                         = camera->CreatePerspectiveProjection(farPlane * cascadeFactors[i - 1], cascade);
            _lightData->FrustumPlaneDistances[_lightData->NumShadowCascades].x = cascade;
        }
        else // If it is outside of the cascade factor array create the cascade from the last entry of the array to the farplane
        {
            float cascade                                                      = farPlane * cascadeFactors[i - 1];
            projection                                                         = camera->CreatePerspectiveProjection(cascade, farPlane);
            _lightData->FrustumPlaneDistances[_lightData->NumShadowCascades].x = farPlane;
        }

        camera->CreateViewFrustumCorners(projection, _frustumCorners);

        // Get Center of view frustum
        glm::vec3 center = glm::vec3(0.0f);
        for (glm::vec4& corner : _frustumCorners) { center += glm::vec3(corner); }
        center /= _frustumCorners.size();

        const glm::mat4 lightView = glm::lookAt(center + lightDirection, center, glm::vec3(0.0f, 1.0f, 0.0f));

        // Get maximum
        constexpr float floatMin = std::numeric_limits<float>::lowest();
        constexpr float floatMax = std::numeric_limits<float>::max();

        // Initialize with opposites
        glm::vec3 min = glm::vec3(floatMax);
        glm::vec3 max = glm::vec3(floatMin);

        for (const glm::vec4& corner : _frustumCorners)
        {
            const glm::vec4 cornerInLightViewSpace = lightView * corner;

            // Select smallest/biggest value so no shadows gets cutoff
            min.x = std::min(min.x, cornerInLightViewSpace.x);
            max.x = std::max(max.x, cornerInLightViewSpace.x);
            min.y = std::min(min.y, cornerInLightViewSpace.y);
            max.y = std::max(max.y, cornerInLightViewSpace.y);
            min.z = std::min(min.z, cornerInLightViewSpace.z);
            max.z = std::max(max.z, cornerInLightViewSpace.z);
        }

        // Scale up z so objects behind the frustum can still cast shadows into the frustum
        float zMult = std::max(zMultiply, std::numeric_limits<float>::min());

        if (min.z < 0) { min.z *= zMult; }
        else { min.z /= zMult; }

        if (max.z < 0) { max.z /= zMult; }
        else { max.z *= zMult; }

        const glm::mat4 lightProjection = glm::ortho(min.x, max.x, min.y, max.y, min.z, max.z);

        _lightData->LightSpaceMatrices[_lightData->NumShadowCascades] = lightProjection * lightView;
        _lightData->NumShadowCascades++;
    }

    _lightData->ShadowLightDirection = glm::vec4(normalize(lightDirection), 1.0);
}
