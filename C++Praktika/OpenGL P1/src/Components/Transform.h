#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "Component.h"


class Transform final : Component
{
    private:
        glm::vec3 _position    = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 _eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 _scale       = glm::vec3(1.0f, 1.0f, 1.0f);

        glm::mat4 _transformationMatrix = glm::mat4(1.0f);
        glm::mat4 _rotationMatrix = glm::mat4(1.0f);
        glm::mat4 _scaleMatrix = glm::mat4(1.0f);
    public:
        glm::vec3 GetPosition() const;
        glm::vec3 GetEulerAngles() const;
        glm::vec3 GetScale() const;

        void Move(const glm::vec3& by);
    
        void SetPosition(const glm::vec3& position);
        void SetEulerAngles(const glm::vec3& eulerAngles);
        void SetScale(const glm::vec3& scale);
    
        glm::mat4 GetTRS() const;
};
