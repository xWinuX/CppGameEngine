#include "GameEngine/Components/Camera.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "GameEngine/Time.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/Window.h"
#include "GameEngine/Rendering/Renderer.h"
#include "GameEngine/Rendering/Primitives/SkyboxCube.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;
using namespace GameEngine;

Camera::Camera(const float fovInDegrees, const float zNear, const float zFar, Shader* frameBufferShader, Material* skyboxMaterial):
    RenderTarget(frameBufferShader),
    _fovInDegrees(fovInDegrees),
    _zNear(zNear),
    _zFar(zFar),
    _skyboxMaterial(skyboxMaterial),
    _skyboxCube(new Rendering::RenderablePrimitive(Primitives::SkyboxCube::GetPrimitive(), skyboxMaterial))
{
    UpdateProjectionMatrix();
    ResizeFrameBuffer(Window::GetCurrentWindow()->GetSize());
    Window::GetCurrentWindow()->AddFramebufferSizeCallback([this](const Window* window)
    {
        ResizeFrameBuffer(window->GetSize());
        UpdateProjectionMatrix();
    });

    _uniformBufferData   = new UniformBufferData();
    _cameraUniformBuffer = new UniformBuffer(reinterpret_cast<unsigned char*>(_uniformBufferData), sizeof(UniformBufferData), 1, GL_DYNAMIC_DRAW);
}

void Camera::OnUpdateEnd()
{
    Renderer::SubmitRenderable(_skyboxCube);
    Renderer::SubmitRenderTarget(this);
}

void Camera::UpdateProjectionMatrix()
{
    const glm::vec2 windowSize = Window::GetCurrentWindow()->GetSize();
    _projectionMatrix          = glm::perspective(glm::radians(_fovInDegrees), windowSize.x / windowSize.y, _zNear, _zFar);
}

glm::mat4 Camera::GetViewMatrix() const { return glm::inverse(GetTransform()->GetTRS()); }

void Camera::OnShaderUse(Rendering::Shader* shader)
{
    shader->GetUniformStorage()->SetUniformInstant<float>("u_Time", Time::GetTimeSinceStart());
}

void Camera::Bind() 
{
    glm::mat4 viewMatrix = GetViewMatrix();
    _uniformBufferData->ViewProjection = _projectionMatrix * viewMatrix;
    _uniformBufferData->Projection = _projectionMatrix;
    _uniformBufferData->ViewPosition = _transform->GetPosition();

    // Remove position from view matrix
    viewMatrix[3][0]     = 0;
    viewMatrix[3][1]     = 0;
    viewMatrix[3][2]     = 0;
    _uniformBufferData->View = viewMatrix;

    _cameraUniformBuffer->UpdateData(reinterpret_cast<unsigned char*>(_uniformBufferData), 1);
    
    _cameraUniformBuffer->Bind(1);
    RenderTarget::Bind();
}

float Camera::GetFOVInDegrees() const { return _fovInDegrees; }

void Camera::SetFOVInDegrees(const float value)
{
    _fovInDegrees = value;
    UpdateProjectionMatrix();
}
