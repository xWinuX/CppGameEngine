#pragma once
#include <glm/ext/matrix_transform.hpp>
#include "../Core/Transform.h"
#include "Component.h"

class TransformComponent final : public Component, public Transform
{
    public:
        void Move(const glm::vec3& vector3);
        void Rotate(const glm::vec3& eulerAngles);
    
        void SetPosition(const glm::vec3& position);
        void SetEulerAngles(const glm::vec3& eulerAngles);
        void SetScale(const glm::vec3& scale);
};
