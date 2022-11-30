#include "Transform.h"
#include <glm/gtc/quaternion.hpp>

glm::vec3 Transform::GetPosition() const { return _position; }
glm::vec3 Transform::GetEulerAngles() const { return _eulerAngles; }
glm::vec3 Transform::GetScale() const { return _scale; }

void Transform::Move(const glm::vec3& vector3)
{
    SetPosition(_position + vector3);
}

void Transform::Rotate(const glm::vec3& eulerAngles)
{
    SetEulerAngles(_eulerAngles + eulerAngles);
}

void Transform::SetPosition(const glm::vec3& position)
{
    _position                   = position;
    _transformationMatrix[3][0] = _position.x;
    _transformationMatrix[3][1] = _position.y;
    _transformationMatrix[3][2] = _position.z;
}

void Transform::SetEulerAngles(const glm::vec3& eulerAngles)
{
    _eulerAngles    = eulerAngles;
    _rotationMatrix = mat4_cast(glm::quat(glm::radians(_eulerAngles)));
}

void Transform::SetScale(const glm::vec3& scale)
{
    _scale             = scale;
    _scaleMatrix[0][0] = _scale.x;
    _scaleMatrix[1][1] = _scale.y;
    _scaleMatrix[2][2] = _scale.z;
}

glm::mat4 Transform::GetTRS() const
{
    return _transformationMatrix * _rotationMatrix * _scaleMatrix;
}
