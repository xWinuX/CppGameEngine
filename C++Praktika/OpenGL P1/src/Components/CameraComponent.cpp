#include "CameraComponent.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "../Application.h"

CameraComponent::CameraComponent(const float fovInDegrees, const float zNear, const float zFar)
{
    const glm::vec2 windowSize = Application::GetWindow().GetSize();
    _projectionMatrix = glm::perspective(fovInDegrees, windowSize.x / windowSize.y, zNear, zFar);
}
