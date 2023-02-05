#pragma once
#include "GameEngine/Rendering/ShaderUseCallback.h"
#include "GameEngine/Rendering/UniformBuffer.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderer;
    }

    namespace Components
    {
        class Light
        {
            friend Rendering::Renderer;

            public:
                static void AddPointLight(const glm::vec3 position, const glm::vec4 color, const float intensity, const float ranges);
                static void AddDirectionalLight(const glm::vec3 direction, const glm::vec4 color, const float intensity);

            protected:
                enum
                {
                    MaxPointLights       = 16,
                    MaxDirectionalLights = 3
                };

                // Note that no vec3 where used to fit the std140 padding rule without creating padding struct members
                struct LightData
                {
                    glm::vec4 AmbientLightColor = glm::vec4(1.0);

                    glm::vec4 PointLightPositions[MaxPointLights]{{0, 0, 0, 0}};
                    glm::vec4 PointLightColors[MaxPointLights]{{1, 1, 1, 1}};
                    glm::vec4 PointLightIntensities[MaxPointLights]{{1, 1, 1, 1}};
                    glm::vec4 PointLightRanges[MaxPointLights]{{1, 1, 1, 1}};

                    glm::vec4 DirectionalLightDirections[MaxDirectionalLights]{{0, 0, 0, 0}};
                    glm::vec4 DirectionalLightColors[MaxDirectionalLights]{{1, 1, 1, 1}};
                    glm::vec4 DirectionalLightIntensities[MaxDirectionalLights]{{1, 1, 1, 1}};
                    
                    float     AmbientIntensity  = 0.5f;
                    int       NumPointLights = 2;
                    int       NumDirectionalLights = 0;
                };

                static LightData* _lightData;

                virtual void OnFrameEnd() = 0;
                static void  Initialize();
                static void  Bind();

            private:
                static UniformBuffer* _lightUniformBuffer;
                static void           Update();
        };
    }
}
