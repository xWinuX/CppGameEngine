#include "CameraControllerPOV.h"

#include "GameEngine/Input.h"
#include "GameEngine/Utils/Math.h"
#include "glm/gtc/quaternion.hpp"

using namespace GameEngine;

glm::vec3 position = glm::vec3(0, 0, 5);

float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;

float speed      = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

void CameraControllerPOV::OnStart()
{
    //glfwSetInputMode(Window::GetCurrentWindow()->GetGlWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CameraControllerPOV::OnLateUpdate()
{
    glm::uvec2 windowSize    = Window::GetCurrentWindow()->GetSize();
    glm::vec2  mousePosition = Input::GetMousePosition();

    // Reset mouse position for next frame
   // glfwSetCursorPos(Window::GetCurrentWindow()->GetGlWindow(), static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 2.0f);

    // Compute new orientation
    horizontalAngle += mouseSpeed * (static_cast<float>(windowSize.x) / 2.0f - mousePosition.x);
    verticalAngle += mouseSpeed * (static_cast<float>(windowSize.y) / 2.0f - mousePosition.y);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
                        cos(verticalAngle) * sin(horizontalAngle),
                        sin(verticalAngle),
                        cos(verticalAngle) * cos(horizontalAngle)
                       );

    // Right vector
    glm::vec3 right = glm::vec3(
                                sin(horizontalAngle - 3.14f / 2.0f),
                                0,
                                cos(horizontalAngle - 3.14f / 2.0f)
                               );

    // Up vector
    glm::vec3 up = glm::cross(right, direction);


    // Camera matrix
    glm::quat lookAt = glm::quatLookAt(
                                       direction, // and looks here : at the same position, plus "direction"
                                       up         // Head is up (set to 0,-1,0 to look upside-down)
                                      );

    
    //_transform->SetRotation(glm::slerp(_transform->GetRotation(), lookAt, 0.3f));
    _transform->SetPosition(glm::mix(_transform->GetPosition(), _followTransform->GetPosition(), 0.5f));
}

void CameraControllerPOV::SetFollowTransform(GameEngine::Components::Transform* followTransform)
{
    _followTransform = followTransform;
}
