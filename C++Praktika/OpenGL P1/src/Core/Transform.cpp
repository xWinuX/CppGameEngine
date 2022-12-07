#include "Transform.h"

#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>

glm::vec3 Transform::GetPosition() const { return _position; }
glm::vec3 Transform::GetEulerAngles() const { return _eulerAngles; }
glm::vec3 Transform::GetScale() const { return _scale; }
glm::mat4 Transform::GetTRS() const
{
    glm::mat4 trs = glm::mat4(1.0f);

    trs = glm::translate(trs, _position);
    
    trs = glm::rotate(trs, glm::radians(_eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
    trs = glm::rotate(trs, glm::radians(_eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
    trs = glm::rotate(trs, glm::radians(_eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));

    trs = glm::scale(trs, _scale);
    
    return trs;
}

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
    _transformationMatrix[0][0] = _scale.x;
    _transformationMatrix[1][1] = _scale.y;
    _transformationMatrix[2][2] = _scale.z;
}

