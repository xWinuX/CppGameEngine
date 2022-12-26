#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "../Application.h"
#include "../Rendering/Renderer.h"

Camera::Camera(const float fovInDegrees, const float zNear, const float zFar) :
    _fovInDegrees(fovInDegrees),
    _zNear(zNear),
    _zFar(zFar)
{
    UpdateProjectionMatrix();
    Application::GetWindow().AddFramebufferSizeCallback([this](Window* window) { UpdateProjectionMatrix(); });
}

void Camera::OnBeforeRender()
{
    Renderer::SetProjectionMatrix(_projectionMatrix);
    Renderer::SetViewMatrix(glm::inverse(GetTransform()->GetTRS()));
}

void Camera::UpdateProjectionMatrix()
{
    const glm::vec2 windowSize = Application::GetWindow().GetSize();
    _projectionMatrix          = glm::perspective(glm::radians(_fovInDegrees), windowSize.x / windowSize.y, _zNear, _zFar);
}

float Camera::GetFOVInDegrees() const { return _fovInDegrees; }

void Camera::SetFOVInDegrees(const float value)
{
    _fovInDegrees = value;
    UpdateProjectionMatrix();   
}
