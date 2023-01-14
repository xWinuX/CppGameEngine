#pragma once

#include <glad/glad.h>

#include "UniformBuffer.h"

#include "../IO/Stream.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Shader
        {
            private:
                GLuint         _programID     = 0;
                UniformBuffer* _uniformBuffer = nullptr;

                static GLuint CompileShader(const std::string& shaderSource, const int type);

                static std::string PreprocessShader(const std::string& shader);

            public:
                Shader(const char* vertexShaderSource, const char* fragmentShaderSource, const char* geometryShaderSource = nullptr);

                ~Shader();

                void Use() const;

                template <typename T>
                void InitializeUniform(const GLchar* uniformName, T defaultValue, const bool includeInApplyQueue = true)
                {
                    _uniformBuffer->InitializeUniform<T>(uniformName, defaultValue, includeInApplyQueue);
                }

                template <typename T>
                void SetUniformInstant(const GLchar* uniformName, T value) { _uniformBuffer->SetUniformInstant<T>(uniformName, value); }

                GLuint GetProgramID() const;

                void UniformBufferFromShader(const Shader* shader);

                UniformBuffer* GetUniformBuffer() const;
                UniformBuffer* GetUniformBufferCopy() const;
        };
    }
}
