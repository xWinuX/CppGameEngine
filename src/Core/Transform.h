#pragma once
#include <glm/ext/matrix_transform.hpp>

class Transform
{
    protected:
        glm::vec3 _position    = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 _eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 _scale       = glm::vec3(1.0f, 1.0f, 1.0f);
    public:
        glm::vec3 GetPosition() const;
        glm::vec3 GetEulerAngles() const;
        glm::vec3 GetScale() const;
        
        glm::mat4 GetTRS() const;

        void Move(const glm::vec3& vector3);
        void Rotate(const glm::vec3& eulerAngles);
        
        void SetPosition(const glm::vec3& position);
        void SetEulerAngles(const glm::vec3& eulerAngles);
        void SetScale(const glm::vec3& scale);
        
};
