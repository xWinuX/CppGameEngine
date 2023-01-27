#include "GameEngine/Components/Transform.h"

#include <glm/fwd.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "GameEngine/Core/GameObject.h"

using namespace GameEngine::Components;
using namespace GameEngine::Core;

glm::vec3 Transform::GetPosition() const { return ToWorldSpace(_localPosition); }
glm::vec3 Transform::GetLocalPosition() const { return _localPosition; }
glm::quat Transform::GetRotation() const { return GetParentRotation() * _localRotation; }
glm::quat Transform::GetLocalRotation() const { return _localRotation; }
glm::vec3 Transform::GetLocalScale() const { return _localScale; }
glm::mat4 Transform::GetTRS() const { return _trs; }

reactphysics3d::Transform& Transform::GetPhysicsTransform() { return _physicsTransform; }


void Transform::SetPosition(const glm::vec3& position) { SetLocalPosition(ToLocalSpace(position)); }
void Transform::SetLocalPosition(const glm::vec3& localPosition)
{
    _localPosition = localPosition;
    _physicsTransform.setPosition(reactphysics3d::Vector3(_localPosition.x, _localPosition.y, _localPosition.z));
}

void Transform::SetRotation(const glm::quat quaternion) { SetLocalRotation(quaternion * GetRotation()); }
void Transform::SetLocalRotation(const glm::quat quaternion)
{
    _localRotation = quaternion;
    _physicsTransform.setOrientation(reactphysics3d::Quaternion(_localRotation.x, _localRotation.y, _localRotation.z, _localRotation.w));
}

void Transform::SetLocalScale(const glm::vec3& scale) { _localScale = scale; }

glm::mat4 Transform::GetParentTRS() const
{
    if (_gameObject->GetParent() != nullptr) { return _gameObject->GetParent()->GetTransform()->GetTRS(); }
    return glm::identity<glm::mat4>();
}

glm::quat Transform::GetParentRotation() const
{
    if (_gameObject->GetParent() != nullptr) { return _gameObject->GetParent()->GetTransform()->GetLocalRotation(); }

    return {1.0f, 0.0f, 0.0f, 0.0f};
}

void Transform::Move(const glm::vec3& vector3) { SetPosition(GetPosition() + vector3); }
void Transform::MoveLocal(const glm::vec3& vector3) { SetLocalPosition(GetLocalPosition() + vector3); }

void Transform::Rotate(const glm::vec3& eulerAngles)
{
    const glm::quat parentRotation = GetParentRotation();
    SetLocalRotation(parentRotation * glm::quat(radians(eulerAngles)) * inverse(parentRotation) * _localRotation);
}
void Transform::RotateLocal(const glm::vec3& eulerAngles) { SetLocalRotation(GetLocalRotation() * glm::quat(radians(eulerAngles))); }


glm::vec3 Transform::ToWorldSpace(const glm::vec3 vec3) const { return GetTRS() * glm::vec4(vec3, 0.0); }
glm::vec3 Transform::ToLocalSpace(const glm::vec3 vec3) const { return inverse(GetParentTRS()) * glm::vec4(vec3, 1.0); }

void Transform::CalculateTRS()
{
    _trs = glm::identity<glm::mat4>();

    _trs *= GetParentTRS();

    _trs = glm::scale(_trs, _localScale);
    _trs = _trs * glm::mat4_cast(_localRotation);
    _trs = glm::translate(_trs, _localPosition);
}

void Transform::OnBeforeRender() { CalculateTRS(); }