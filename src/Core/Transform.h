#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "glm/gtc/quaternion.hpp"
#include "reactphysics3d/mathematics/Transform.h"

namespace GameEngine
{
    namespace Core
    {
        class Transform
        {
            protected:
                glm::vec3                 _position         = glm::vec3(0.0f, 0.0f, 0.0f);
                glm::vec3                 _eulerAngles      = glm::vec3(0.0f, 0.0f, 0.0f);
                glm::vec3                 _scale            = glm::vec3(1.0f, 1.0f, 1.0f);
            
                reactphysics3d::Transform _physicsTransform = reactphysics3d::Transform(
                                                                                        reactphysics3d::Vector3(_position.x, _position.y, _position.z),
                                                                                        reactphysics3d::Quaternion::fromEulerAngles(glm::radians(_eulerAngles.x),
                                                                                            glm::radians(_eulerAngles.y), glm::radians(_eulerAngles.z))
                                                                                       );

            public:
                glm::vec3 GetPosition() const;
                glm::vec3 GetEulerAngles() const;
                glm::vec3 GetScale() const;

                glm::mat4 GetTRS() const;

                void Move(const glm::vec3& vector3);
                void Rotate(const glm::vec3& eulerAngles);

                void SetPosition(const glm::vec3& position);
                void SetRotation(const glm::quat quaternion);
                void SetEulerAngles(const glm::vec3& eulerAngles);
                void SetScale(const glm::vec3& scale);

                reactphysics3d::Transform& GetPhysicsTransform();
        };
    }
}
