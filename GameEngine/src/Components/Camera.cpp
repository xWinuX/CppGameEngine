#include "GameEngine/Components/Camera.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "GameEngine/Time.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/Window.h"
#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;
using namespace GameEngine;

Camera::Camera(const float fovInDegrees, const float zNear, const float zFar, Shader* frameBufferShader):
    RenderTarget(frameBufferShader),
    _fovInDegrees(fovInDegrees),
    _zNear(zNear),
    _zFar(zFar)
{
    UpdateProjectionMatrix();
    ResizeFrameBuffer(Window::GetCurrentWindow()->GetSize());
    Window::GetCurrentWindow()->AddFramebufferSizeCallback([this](const Window* window)
    {
        ResizeFrameBuffer(window->GetSize());
        UpdateProjectionMatrix();
    });
}

void Camera::OnUpdateEnd()
{
    Renderer::SubmitRenderTarget(this);
}

void Camera::UpdateProjectionMatrix()
{
    const glm::vec2 windowSize = Window::GetCurrentWindow()->GetSize();
    _projectionMatrix          = glm::perspective(glm::radians(_fovInDegrees), windowSize.x / windowSize.y, _zNear, _zFar);
}

void Camera::OnShaderUse(Rendering::Shader* shader)
{
    const glm::mat4 viewMatrix = glm::inverse(GetTransform()->GetTRS());
    
    shader->GetUniformStorage()->SetUniformInstant<float>("u_Time", Time::GetTimeSinceStart());
    shader->GetUniformStorage()->SetUniformInstant<glm::mat4>("u_ViewProjection", _projectionMatrix * viewMatrix);
    shader->GetUniformStorage()->SetUniformInstant<glm::vec3>("u_ViewPosition", _transform->GetPosition());
}

float Camera::GetFOVInDegrees() const { return _fovInDegrees; }

void Camera::SetFOVInDegrees(const float value)
{
    _fovInDegrees = value;
    UpdateProjectionMatrix();
}
