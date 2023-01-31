#include "GameEngine/Components/Transform.h"

#include <glm/fwd.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "GameEngine/GameObject.h"

using namespace GameEngine::Components;

const glm::vec4 Transform::Right   = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
const glm::vec4 Transform::Up      = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
const glm::vec4 Transform::Forward = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

glm::vec3 Transform::GetPosition() const { return ToWorldSpace(_localPosition); }
glm::vec3 Transform::GetLocalPosition() const { return _localPosition; }
glm::quat Transform::GetRotation() const { return GetParentRotation() * _localRotation; }
glm::quat Transform::GetLocalRotation() const { return _localRotation; }
glm::vec3 Transform::GetLocalScale() const { return _localScale; }

glm::vec3 Transform::GetRight() const { return mat4_cast(GetRotation()) * Right; }
glm::vec3 Transform::GetUp() const { return mat4_cast(GetRotation()) * Up; }
glm::vec3 Transform::GetForward() const { return mat4_cast(GetRotation()) * Forward; }

/**
 * \brief
 * Returns the TransformationRotationScale matrix of the transform
 * \n \n
 * IMPORTANT: The TRS is only calculated at the end of the update cycle for performance reasons,
 * if you need the TRS immediately after a transformation call CalculateTRS() before GetTRS()
 * 
 * \return Matrix4x4 TRS
 */
glm::mat4 Transform::GetTRS() const { return _trs; }

reactphysics3d::Transform& Transform::GetPhysicsTransform() { return _physicsTransform; }

void Transform::SetPosition(const glm::vec3& position) { SetLocalPosition(ToLocalSpace(position)); }

void Transform::SetLocalPosition(const glm::vec3& localPosition)
{
    _localPosition = localPosition;
    _physicsTransform.setPosition(reactphysics3d::Vector3(_localPosition.x, _localPosition.y, _localPosition.z));
    CalculateTRS();
}

void Transform::SetRotation(const glm::quat quaternion) { SetLocalRotation(GetParentRotation() * quaternion); }

void Transform::SetLocalRotation(const glm::quat quaternion)
{
    _localRotation = quaternion;
    //_physicsTransform.setOrientation(reactphysics3d::Quaternion(_localRotation.x, _localRotation.y, _localRotation.z, _localRotation.w));
    CalculateTRS();
}

void Transform::SetLocalScale(const glm::vec3& scale)
{
    _localScale = scale;
    CalculateTRS();
}


glm::quat Transform::GetParentRotation() const
{
    if (_gameObject->GetParent() != nullptr) { return _gameObject->GetParent()->GetTransform()->GetRotation(); }

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


glm::vec3 Transform::ToWorldSpace(const glm::vec3 vec3) const { return GetParentTRS() * glm::vec4(vec3, 1.0f); }
glm::vec3 Transform::ToLocalSpace(const glm::vec3 vec3) const { return inverse(GetParentTRS()) * glm::vec4(vec3, 0.0f); }


glm::mat4 Transform::GetParentTRS() const
{
    if (_gameObject->GetParent() != nullptr)
    {
        _gameObject->GetParent()->GetTransform()->CalculateTRS();
        return _gameObject->GetParent()->GetTransform()->GetTRS();
    }
    return glm::identity<glm::mat4>();
}

void Transform::CalculateTRS()
{
    _trs =
        GetParentTRS()
        * glm::translate(glm::identity<glm::mat4>(), _localPosition)
        * mat4_cast(_localRotation)
        * glm::scale(glm::identity<glm::mat4>(), _localScale);
}

void Transform::OnUpdateEnd() { CalculateTRS(); }
