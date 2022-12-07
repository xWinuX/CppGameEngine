#pragma once
#include <glm/ext/matrix_transform.hpp>


#include "Component.h"

class CameraComponent final : public Component
{
    private:
        glm::mat4 _projectionMatrix = glm::identity<glm::mat4>();
    public:
        CameraComponent(float fovInDegrees, float zNear, float zFar);
        void OnPreDraw() override;
        
};
