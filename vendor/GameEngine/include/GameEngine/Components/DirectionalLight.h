#pragma once
#include <vector>

#include "GameEngine/Components/Component.h"
#include "GameEngine/Rendering/FrameBuffer.h"
#include "GameEngine/Rendering/CascadedShadowMap.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/constants.hpp"

namespace GameEngine
{
    namespace Components
    {
        class DirectionalLight : public Component
        {
            private:
                static std::vector<glm::vec3> _directions;
                static std::vector<glm::vec4> _colors;
                static std::vector<float>     _intensities;

                Rendering::CascadedShadowMap* _shadowMap;
            
                glm::vec3 _eulerAngles = glm::zero<glm::vec3>();
                glm::vec4 _color;
                float     _intensity;

            protected:
                void OnUpdateEnd() override;

            public:
                explicit DirectionalLight(const glm::vec4 color = glm::vec4(1.0), const float intensity = 1.0f);

                void SetColor(glm::vec4 color);
                void SetIntensity(float intensity);
        };
    }
}
