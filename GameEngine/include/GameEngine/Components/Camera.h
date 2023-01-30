#pragma once
#include <glm/ext/matrix_transform.hpp>
#include "Component.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameEngine/Rendering/FrameBuffer.h"
#include "GameEngine/Rendering/RenderTarget.h"

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
            
                void UpdateProjectionMatrix();

                void OnShaderUse(Rendering::Shader* shader) override;

            protected:
                void OnUpdateEnd() override;

            public:
                Camera(float fovInDegrees, float zNear, float zFar, Rendering::Shader* frameBufferShader);
                float GetFOVInDegrees() const;
                void  SetFOVInDegrees(float value);
        };
    }
}
