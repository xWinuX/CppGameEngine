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
        glm::vec4                     _color;

    public:
        explicit PointLight(Shader* shader, const glm::vec4 color = glm::vec4(1.0)):
            Light(shader),
            _color(color) {}

        void OnBeforeRender() override;
        void OnFrameEnd() override;
        void OnShaderUse() override;

        void SetColor(glm::vec4 color);
};
