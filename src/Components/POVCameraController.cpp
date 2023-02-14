#include "POVCameraController.h"

#include "GameEngine/Input.h"
#include "GameEngine/GUIManager.h"
#include "GameEngine/Utils/Math.h"
#include "glm/gtc/quaternion.hpp"

using namespace GameEngine;


void POVCameraController::OnLateUpdate()
{
    const glm::vec2 mousePosition = Input::GetMousePosition();

    // Compute new orientation
    const glm::vec2 mouseDelta = Input::GetMouseDelta() * _mouseSpeed;
    _currentAngle.x += mouseDelta.x;
    _currentAngle.y += mouseDelta.y;

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    const float     cosAngleY = cos(_currentAngle.y);
    const glm::vec3 direction = glm::vec3(
                                          cosAngleY * sin(_currentAngle.x),
                                          sin(_currentAngle.y),
                                          cosAngleY * cos(_currentAngle.x)
                                         );

    // Right vector
    const float     xAngleRads = _currentAngle.x - glm::pi<float>() / 2.0f;
    const glm::vec3 right      = glm::vec3(
                                           sin(xAngleRads),
                                           0,
                                           cos(xAngleRads)
                                          );

    // Up vector
    const glm::vec3 up = glm::cross(right, direction);

    // Camera matrix
    const glm::quat lookAt = glm::quatLookAt(direction, up);

    // Only update rotation if gui isn't visiable
    if (GUIManager::IsHidden()) { _transform->SetRotation(glm::slerp(_transform->GetRotation(), lookAt, 0.3f)); }

    _transform->SetPosition(glm::mix(_transform->GetPosition(), _followTransform->GetPosition(), 0.5f));

    _previousMousePosition = mousePosition;
}

POVCameraController::POVCameraController():
    Component("POV Camera Controller") {}

void POVCameraController::SetFollowTransform(GameEngine::Components::Transform* followTransform) { _followTransform = followTransform; }
