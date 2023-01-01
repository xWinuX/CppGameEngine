#pragma once

#include "Component.h"
#include "Light.h"
#include "glm/vec3.hpp"
#include "../Rendering/Shader.h"

class PointLight final : public Light
{
    private:
        static std::vector<glm::vec3> _positions;
        static std::vector<glm::vec4> _colors;
        static std::vector<float>     _intensities;
        static std::vector<float>     _ranges;

        glm::vec4 _color;
        float     _range;
        float     _intensity;

    public:
        explicit PointLight(Shader* shader, const glm::vec4 color = glm::vec4(1.0), const float range = 1.0f, const float intensity = 1.0f):
            Light(shader),
            _color(color),
            _range(range),
            _intensity(intensity) {}

        void OnBeforeRender() override;
        void OnFrameEnd() override;
        void OnShaderUse() override;

        void SetColor(glm::vec4 color);
        void SetRange(float range);
        void SetIntensity(float intensity);
};
