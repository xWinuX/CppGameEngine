#pragma once
#include "Component.h"
#include "glm/vec3.hpp"
#include "glm/ext/quaternion_float.hpp"
#include "reactphysics3d/mathematics/Transform.h"

namespace GameEngine
{
    namespace Components
    {
        class Transform final : public Component
        {
            private:
                glm::vec3 _localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
                glm::quat _localRotation = glm::identity<glm::quat>();
                glm::vec3 _localScale    = glm::vec3(1.0f, 1.0f, 1.0f);
                glm::mat4 _trs           = glm::identity<glm::mat4>();

                reactphysics3d::Transform _physicsTransform = reactphysics3d::Transform(
                                                                                        reactphysics3d::Vector3(_localPosition.x, _localPosition.y, _localPosition.z),
                                                                                        reactphysics3d::Quaternion(_localRotation.x, _localRotation.y, _localRotation.z,
                                                                                                                   _localRotation.w)
                                                                                       );

                glm::mat4 GetParentTRS() const;
                glm::quat GetParentRotation() const;

            public:
                glm::vec3 GetPosition() const;
                glm::vec3 GetLocalPosition() const;
                glm::quat GetRotation() const;
                glm::quat GetLocalRotation() const;
                glm::vec3 GetLocalScale() const;

                glm::mat4 GetTRS() const;

                void CalculateTRS();

                void Move(const glm::vec3& vector3);
                void Rotate(const glm::vec3& eulerAngles);
                void MoveLocal(const glm::vec3& vector3);
                void RotateLocal(const glm::vec3& eulerAngles);

                void SetPosition(const glm::vec3& position);
                void SetLocalPosition(const glm::vec3& localPosition);
                void SetRotation(const glm::quat quaternion);
                void SetLocalRotation(const glm::quat quaternion);
                void SetLocalScale(const glm::vec3& scale);

                glm::vec3 ToWorldSpace(glm::vec3 vec3) const;
                glm::vec3 ToLocalSpace(glm::vec3 vec3) const;

                reactphysics3d::Transform& GetPhysicsTransform();

                void OnBeforeRender() override;
        };
    }
}
