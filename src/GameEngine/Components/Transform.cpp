#include "Transform.h"


#include <iostream>
#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../Core/GameObject.h"
#include "glm/gtx/euler_angles.hpp"
#include "glm/ext/matrix_float4x4.hpp"

using namespace GameEngine::Components;
using namespace GameEngine::Core;

glm::vec3 Transform::GetPosition() const { return _position; }
glm::quat Transform::GetRotation() const { return _rotation; }
glm::vec3 Transform::GetScale() const { return _scale; }

glm::mat4 Transform::GetTRS() const
{
    glm::mat4 trs = glm::identity<glm::mat4>();
    
    const GameObject* parent = _gameObject->GetParent();
    while (parent != nullptr)
    {
        trs *= parent->GetTransform()->GetTRS();
        parent = parent->GetParent();
    }

    trs = glm::translate(trs, _position);
    trs = trs * glm::mat4_cast(_rotation);
    trs = glm::scale(trs, _scale);
    
    return trs;
}

void Transform::Move(const glm::vec3& vector3) { SetPosition(_position + vector3); }

void Transform::Rotate(const glm::vec3& eulerAngles) { SetRotation(_rotation * glm::quat(radians(eulerAngles))); }

void Transform::SetPosition(const glm::vec3& position)
{
    _position = position;
    _physicsTransform.setPosition(reactphysics3d::Vector3(_position.x, _position.y, _position.z));
}

void Transform::SetRotation(const glm::quat quaternion) { _rotation = quaternion; }

void Transform::SetScale(const glm::vec3& scale) { _scale = scale; }

reactphysics3d::Transform& Transform::GetPhysicsTransform() { return _physicsTransform; }
