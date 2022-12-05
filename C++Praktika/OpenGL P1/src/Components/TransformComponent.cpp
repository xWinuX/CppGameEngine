#include "TransformComponent.h"
#include <glm/gtc/quaternion.hpp>

void TransformComponent::Move(const glm::vec3& vector3)
{
    SetPosition(_position + vector3);
}

void TransformComponent::Rotate(const glm::vec3& eulerAngles)
{
    SetEulerAngles(_eulerAngles + eulerAngles);
}

void TransformComponent::SetPosition(const glm::vec3& position)
{
    _position                   = position;
    _transformationMatrix[3][0] = _position.x;
    _transformationMatrix[3][1] = _position.y;
    _transformationMatrix[3][2] = _position.z;
}

void TransformComponent::SetEulerAngles(const glm::vec3& eulerAngles)
{
    _eulerAngles    = eulerAngles;
    _rotationMatrix = mat4_cast(glm::quat(glm::radians(_eulerAngles)));
}

void TransformComponent::SetScale(const glm::vec3& scale)
{
    _scale             = scale;
    _scaleMatrix[0][0] = _scale.x;
    _scaleMatrix[1][1] = _scale.y;
    _scaleMatrix[2][2] = _scale.z;
}

