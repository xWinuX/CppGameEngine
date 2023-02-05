#pragma once

#include "Component.h"

#include "glm/vec3.hpp"
#include "../Rendering/Shader.h"

namespace GameEngine
{
    namespace Components
    {
        class PointLight final : public Component
        {
            private:
                static std::vector<glm::vec3> _positions;
                static std::vector<glm::vec4> _colors;
                static std::vector<float>     _intensities;
                static std::vector<float>     _ranges;

                glm::vec4 _color;
                float     _range;
                float     _intensity;

            protected:
                void OnUpdateEnd() override;

            public:
                explicit PointLight(const glm::vec4 color = glm::vec4(1.0), const float range = 1.0f, const float intensity = 1.0f);

                void SetColor(glm::vec4 color);
                void SetRange(float range);
                void SetIntensity(float intensity);
        };
    }
}
