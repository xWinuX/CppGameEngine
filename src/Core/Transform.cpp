#include "Transform.h"

#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace GameEngine::Core;

glm::vec3 Transform::GetPosition() const { return _position; }
glm::vec3 Transform::GetEulerAngles() const { return _eulerAngles; }
glm::vec3 Transform::GetScale() const { return _scale; }

glm::mat4 Transform::GetTRS() const
{
    glm::mat4 trs = glm::identity<glm::mat4>();

    trs = glm::translate(trs, _position);


    trs = trs * mat4_cast(_rotation);

    /*
    trs = glm::rotate(trs, glm::radians(_eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
    trs = glm::rotate(trs, glm::radians(_eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
    trs = glm::rotate(trs, glm::radians(_eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
    */

    trs = glm::scale(trs, _scale);

    return trs;
}

void Transform::Move(const glm::vec3& vector3) { SetPosition(_position + vector3); }
void Transform::Rotate(const glm::vec3& eulerAngles) { SetEulerAngles(_eulerAngles + eulerAngles); }

void Transform::SetPosition(const glm::vec3& position)
{
    _position = position;
    _physicsTransform.setPosition(reactphysics3d::Vector3(_position.x, _position.y, _position.z));
}

void Transform::SetRotation(const glm::quat quaternion) { _rotation = quaternion; }

void Transform::SetEulerAngles(const glm::vec3& eulerAngles) { _eulerAngles = eulerAngles; }
void Transform::SetScale(const glm::vec3& scale) { _scale = scale; }

reactphysics3d::Transform& Transform::GetPhysicsTransform() { return _physicsTransform; }
