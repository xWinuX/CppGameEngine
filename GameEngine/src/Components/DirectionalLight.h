#pragma once
#include <vector>

#include "GameEngine/Components/Light.h"
#include "GameEngine/Rendering/Shader.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/constants.hpp"

class DirectionalLight : public GameEngine::Components::Light
{
    private:
        static std::vector<glm::vec3> _directions;
        static std::vector<glm::vec4> _colors;
        static std::vector<float>     _intensities;

        glm::vec3 _eulerAngles = glm::zero<glm::vec3>();
        glm::vec4 _color;
        float     _intensity;

    protected:
        void OnUpdateEnd() override;
        void OnFrameEnd() override;
        void OnShaderUse(GameEngine::Rendering::Shader* shader) override;

    public:
        explicit DirectionalLight(const glm::vec4 color = glm::vec4(1.0), const float intensity = 1.0f);

        void SetColor(glm::vec4 color);
        void SetIntensity(float intensity);
};
