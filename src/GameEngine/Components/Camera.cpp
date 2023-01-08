#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "../Core/Window.h"
#include "../Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;
using namespace GameEngine::Core;

Camera::Camera(const float fovInDegrees, const float zNear, const float zFar) :
    _fovInDegrees(fovInDegrees),
    _zNear(zNear),
    _zFar(zFar)
{
    UpdateProjectionMatrix();
    Window::GetCurrentWindow()->AddFramebufferSizeCallback([this](Window* window) { UpdateProjectionMatrix(); });
}

void Camera::OnBeforeRender()
{
    Renderer::SetProjectionMatrix(_projectionMatrix);
    Renderer::SetViewMatrix(glm::inverse(GetTransform()->GetTRS()));
}

void Camera::UpdateProjectionMatrix()
{
    const glm::vec2 windowSize = Window::GetCurrentWindow()->GetSize();
    _projectionMatrix          = glm::perspective(glm::radians(_fovInDegrees), windowSize.x / windowSize.y, _zNear, _zFar);
}

float Camera::GetFOVInDegrees() const { return _fovInDegrees; }

void Camera::SetFOVInDegrees(const float value)
{
    _fovInDegrees = value;
    UpdateProjectionMatrix();   
}
