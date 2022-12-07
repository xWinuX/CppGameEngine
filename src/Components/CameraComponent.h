#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "Component.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Core/Window.h"

class CameraComponent final : public Component
{
    private:
        float _fovInDegrees;
        float _zNear;
        float _zFar;
        glm::mat4 _projectionMatrix = glm::identity<glm::mat4>();
    public:
        CameraComponent(float fovInDegrees, float zNear, float zFar);
        void OnPreDraw() override;
        void ResizeProjectionMatrix(Window* window);
        
};
