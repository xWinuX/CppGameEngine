#pragma once
#include <glm/ext/matrix_transform.hpp>
#include "Component.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GameEngine
{
    namespace Components
    {
        class Camera final : public Component
        {
            private:
                float     _fovInDegrees;
                float     _zNear;
                float     _zFar;
                glm::mat4 _projectionMatrix = glm::identity<glm::mat4>();

                void UpdateProjectionMatrix();

            protected:
                void OnUpdateEnd() override;

            public:
                Camera(float fovInDegrees, float zNear, float zFar);
                float GetFOVInDegrees() const;
                void  SetFOVInDegrees(float value);
        };
    }
}
