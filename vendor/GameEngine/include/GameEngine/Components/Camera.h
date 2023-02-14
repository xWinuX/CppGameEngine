#pragma once
#include <glm/ext/matrix_transform.hpp>
#include "Component.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameEngine/Rendering/RenderablePrimitive.h"
#include "GameEngine/Rendering/RenderTarget.h"
#include "GameEngine/Rendering/UniformBuffer.h"

namespace GameEngine
{
    namespace Components
    {
        class Camera final : public Component, public Rendering::RenderTarget
        {
            private:
                static Camera*         _main;
                float                  _fovInDegrees;
                float                  _nearPlane;
                float                  _farPlane;
                glm::uvec2             _projectionSize;
                glm::mat4              _projectionMatrix   = glm::identity<glm::mat4>();
                glm::mat4              _uiProjectionMatrix = glm::identity<glm::mat4>();
                std::vector<glm::vec4> _viewFrustumCorners = std::vector<glm::vec4>(8);

                Rendering::RenderablePrimitive* _skyboxCube;

                struct UniformBufferData
                {
                    glm::mat4 ViewProjection = glm::identity<glm::mat4>();
                    glm::mat4 Projection     = glm::identity<glm::mat4>();
                    glm::mat4 UIProjection   = glm::identity<glm::mat4>();
                    glm::mat4 View           = glm::identity<glm::mat4>();
                    glm::vec4 ViewPosition   = glm::zero<glm::vec4>();
                    float     FarPlane       = 50;
                };

                UniformBufferData* _uniformBufferData;
                UniformBuffer*     _cameraUniformBuffer;

                void UpdateViewFrustumCorners();
                void UpdateProjectionMatrix();
                void OnShaderUse(Rendering::Shader* shader) override;
                void Bind() override;

            protected:
                void OnUpdateEnd() override;
                void OnGuiDraw() override;

            public:
                Camera(float fovInDegrees, float zNear, float zFar, Rendering::Material* frameBufferMaterial, Rendering::Material* skyboxMaterial);
                float                   GetFOVInDegrees() const;
                void                    SetFOVInDegrees(float value);
                float                   GetNearPlan() const;
                float                   GetFarPlan() const;
                glm::mat4               GetViewMatrix() const;
                glm::mat4               CreatePerspectiveProjection(const float nearPlan, const float farPlane) const;
                std::vector<glm::vec4>  CreateViewFrustumCorners(float nearPlane, float farPlane) const;
                void                    CreateViewFrustumCorners(glm::mat4 projectionMatrix, std::vector<glm::vec4>& vector) const;
                std::vector<glm::vec4>& GetViewFrustumCorners();
                static Camera*          GetMain();
        };
    }
}
