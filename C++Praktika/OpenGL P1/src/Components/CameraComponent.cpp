#include "CameraComponent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/ext/matrix_clip_space.hpp>

#include "../Application.h"
#include "../Rendering/Renderer.h"

CameraComponent::CameraComponent(const float fovInDegrees, const float zNear, const float zFar)
{
    const glm::vec2 windowSize = Application::GetWindow().GetSize();
    _projectionMatrix = glm::perspective(fovInDegrees, windowSize.x / windowSize.y, zNear, zFar);
}

void CameraComponent::OnPreDraw()
{
    Renderer::SetProjectionMatrix(_projectionMatrix);
    Renderer::SetViewMatrix(GetTransform()->GetTRS());
}
