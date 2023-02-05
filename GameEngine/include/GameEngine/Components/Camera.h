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
                float     _fovInDegrees;
                float     _zNear;
                float     _zFar;
                glm::mat4 _projectionMatrix = glm::identity<glm::mat4>();

                Rendering::Material*            _skyboxMaterial;
                Rendering::RenderablePrimitive* _skyboxCube;


                struct UniformBufferData
                {
                    glm::mat4 ViewProjection = glm::identity<glm::mat4>();
                    glm::mat4 Projection     = glm::identity<glm::mat4>();
                    glm::mat4 View           = glm::identity<glm::mat4>();
                    glm::vec3 ViewPosition   = glm::zero<glm::vec3>();
                };

                UniformBufferData* _uniformBufferData;
                UniformBuffer*     _cameraUniformBuffer;

                void UpdateProjectionMatrix();

                void OnShaderUse(Rendering::Shader* shader) override;

                void Bind()  override;

            protected:
                void OnUpdateEnd() override;

            public:
                Camera(float fovInDegrees, float zNear, float zFar, Rendering::Shader* frameBufferShader, Rendering::Material* skyboxMaterial);
                float     GetFOVInDegrees() const;
                void      SetFOVInDegrees(float value);
                glm::mat4 GetViewMatrix() const;
        };
    }
}
