#include "GameEngine/Rendering/Light.h"

#include "GameEngine/Components/Camera.h"
#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;

Light::UniformBufferData* Light::_lightData          = new Light::UniformBufferData();
UniformBuffer*            Light::_lightUniformBuffer = nullptr;
std::vector<glm::vec4>    Light::_frustumCorners     = std::vector<glm::vec4>(8);

void Light::Initialize()
{
    _lightUniformBuffer = new UniformBuffer(reinterpret_cast<unsigned char*>(_lightData), sizeof(Light::UniformBufferData), 1, GL_DYNAMIC_DRAW);
    _lightUniformBuffer->Bind(2);
}


void Light::Update()
{
    _lightUniformBuffer->UpdateData(reinterpret_cast<const unsigned char*>(_lightData), 1);

    _lightData->NumDirectionalLights = 0;
    _lightData->NumPointLights       = 0;
    _lightData->NumShadowCascades    = 0;
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

void Light::SetShadowCaster(const glm::vec3 lightDirection)
{
    Camera* camera = Camera::GetMain();

    float nearPlane = camera->GetNearPlan();
    float farPlane  = camera->GetFarPlan();

    std::vector<float> cascades = std::vector<float>({ farPlane / 50.0f, farPlane / 25.0f, farPlane / 10.0f, farPlane / 2.0f });
    
    for (unsigned int i = 0; i < cascades.size()+1; i++)
    {
        _frustumCorners.clear();
        
        glm::mat4 projection;
        if (i == 0)
        {
            projection = camera->CreatePerspectiveProjection(nearPlane, cascades[i]);
            _lightData->FrustumPlaneDistances[_lightData->NumShadowCascades].x = cascades[i];
        }
        else if (i < cascades.size())
        {
            projection = camera->CreatePerspectiveProjection(cascades[i-1], cascades[i]);
            _lightData->FrustumPlaneDistances[_lightData->NumShadowCascades].x = cascades[i];
        }
        else
        {
            projection = camera->CreatePerspectiveProjection(cascades[i-1], farPlane);
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

        // Scale up z so object behind the frustum can still cast shadows into the frustum
        constexpr float zMult = 10.0f;

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
