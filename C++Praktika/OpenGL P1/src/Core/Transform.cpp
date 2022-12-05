#include "Transform.h"

glm::vec3 Transform::GetPosition() const { return _position; }
glm::vec3 Transform::GetEulerAngles() const { return _eulerAngles; }
glm::vec3 Transform::GetScale() const { return _scale; }
glm::mat4 Transform::GetTRS() const { return _transformationMatrix * _rotationMatrix * _scaleMatrix; }
