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
                bool _isShadowCaster;

                glm::vec3            _eulerAngles = glm::zero<glm::vec3>();
                glm::vec4            _color;
                std::array<float, 4> _cascadeFactors = {0.02f, 0.04f, 0.1f, 0.5f};
                float                _intensity;

            protected:
                void OnUpdate() override;
                void OnUpdateEnd() override;

            public:
                explicit DirectionalLight(const bool isShadowCaster = false, const glm::vec4 color = glm::vec4(1.0), const float intensity = 1.0f);

                void SetColor(glm::vec4 color);
                void SetIntensity(float intensity);
        };
    }
}
