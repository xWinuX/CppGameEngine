#include "CameraComponent.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "../Application.h"
#include "../Rendering/Renderer.h"

CameraComponent::CameraComponent(const float fovInDegrees, const float zNear, const float zFar) :
    _fovInDegrees(fovInDegrees),
    _zNear(zNear),
    _zFar(zFar)
{
    UpdateProjectionMatrix();
    Application::GetWindow().AddFramebufferSizeCallback([this](Window* window) { UpdateProjectionMatrix(); });
}

void CameraComponent::OnPreDraw()
{
    Renderer::SetProjectionMatrix(_projectionMatrix);
    Renderer::SetViewMatrix(glm::inverse(GetTransform()->GetTRS()));
}


void CameraComponent::UpdateProjectionMatrix()
{
    const glm::vec2 windowSize = Application::GetWindow().GetSize();
    _projectionMatrix          = glm::perspective(glm::radians(_fovInDegrees), windowSize.x / windowSize.y, _zNear, _zFar);
}

float CameraComponent::GetFOVInDegrees() const { return _fovInDegrees; }

void CameraComponent::SetFOVInDegrees(const float value)
{
    _fovInDegrees = value;
    UpdateProjectionMatrix();   
}
