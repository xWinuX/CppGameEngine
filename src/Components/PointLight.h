#pragma once
#include <vector>

#include "Component.h"
#include "Light.h"
#include "glm/vec3.hpp"
#include "../Rendering/Shader.h"

class PointLight final : public Light
{
    private:
        static std::vector<glm::vec3> _positions;

    public:
        explicit PointLight(Shader* shader):
            Light(shader) {}

        void OnShaderUse() override;
};
