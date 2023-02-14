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

Camera* Camera::_main = nullptr;

Camera::Camera(const float fovInDegrees, const float zNear, const float zFar, Material* frameBufferMaterial, Material* skyboxMaterial):
    Component("Camera"),
    RenderTarget(frameBufferMaterial),
    _fovInDegrees(fovInDegrees),
    _nearPlane(zNear),
    _farPlane(zFar),
    _skyboxCube(new Rendering::RenderablePrimitive(Primitives::SkyboxCube::GetPrimitive(), skyboxMaterial))
{
    if (_main == nullptr) { _main = this; }

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
    UpdateViewFrustumCorners();
    Renderer::SubmitRenderable(_skyboxCube);
    Renderer::SubmitRenderTarget(this);
}

void Camera::CreateViewFrustumCorners(const glm::mat4 projectionMatrix, std::vector<glm::vec4>& vector) const
{
    const glm::mat4 inverseViewProjection = glm::inverse(projectionMatrix * GetViewMatrix());

    for (unsigned int x = 0; x < 2; ++x)
    {
        for (unsigned int y = 0; y < 2; ++y)
        {
            for (unsigned int z = 0; z < 2; ++z)
            {
                const glm::vec4 pt =
                    inverseViewProjection * glm::vec4(
                                                      2.0f * static_cast<float>(x) - 1.0f,
                                                      2.0f * static_cast<float>(y) - 1.0f,
                                                      2.0f * static_cast<float>(z) - 1.0f,
                                                      1.0f);
                vector.push_back(pt / pt.w);
            }
        }
    }
}

void Camera::UpdateViewFrustumCorners()
{
    _viewFrustumCorners.clear();
    CreateViewFrustumCorners(_projectionMatrix, _viewFrustumCorners);
}

glm::mat4 Camera::CreatePerspectiveProjection(const float nearPlan, const float farPlane) const
{
    return glm::perspective(glm::radians(_fovInDegrees), static_cast<float>(_projectionSize.x) / static_cast<float>(_projectionSize.y), nearPlan, farPlane);
}

void Camera::UpdateProjectionMatrix()
{
    _projectionSize   = Window::GetCurrentWindow()->GetSize();
    _projectionMatrix = CreatePerspectiveProjection(_nearPlane, _farPlane);
}

glm::mat4 Camera::GetViewMatrix() const { return glm::inverse(GetTransform()->GetTRS()); }

std::vector<glm::vec4>& Camera::GetViewFrustumCorners() { return _viewFrustumCorners; }

std::vector<glm::vec4> Camera::CreateViewFrustumCorners(const float nearPlane, const float farPlane) const
{
    std::vector<glm::vec4> corners    = std::vector<glm::vec4>(8);
    const glm::mat4        projection = CreatePerspectiveProjection(nearPlane, farPlane);

    CreateViewFrustumCorners(projection, corners);

    return corners;
}

Camera* Camera::GetMain() { return _main; }

void Camera::OnShaderUse(Rendering::Shader* shader) { shader->GetUniformStorage()->SetUniformInstant<float>("u_Time", Time::GetTimeSinceStart()); }

void Camera::Bind()
{
    glm::mat4 viewMatrix               = GetViewMatrix();
    _uniformBufferData->ViewProjection = _projectionMatrix * viewMatrix;
    _uniformBufferData->Projection     = _projectionMatrix;
    _uniformBufferData->ViewPosition   = glm::vec4(_transform->GetPosition(), 1.0);
    _uniformBufferData->FarPlane       = _farPlane;

    // Remove position from view matrix
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

float Camera::GetNearPlan() const { return _nearPlane; }

float Camera::GetFarPlan() const { return _farPlane; }
