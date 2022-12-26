#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "Component.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Core/Window.h"

class Camera final : public Component
{
    private:
        float _fovInDegrees;
        float _zNear;
        float _zFar;
        glm::mat4 _projectionMatrix = glm::identity<glm::mat4>();
        void UpdateProjectionMatrix();
    public:
        Camera(float fovInDegrees, float zNear, float zFar);
        void  OnBeforeRender() override;
        float GetFOVInDegrees() const;
        void SetFOVInDegrees(float value);
};
