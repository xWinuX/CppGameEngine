#pragma once

#include <glad/glad.h>

#include "UniformStorage.h"

#include "../IO/Stream.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Shader
        {
            private:
                GLuint          _programID      = 0;
                UniformStorage* _uniformStorage = nullptr;

                static GLuint CompileShader(const std::string& shaderSource, const int type);

                static std::string PreprocessShader(const std::string& shader);

            public:
                Shader(const char* vertexShaderSource, const char* fragmentShaderSource, const char* geometryShaderSource = nullptr);

                ~Shader();

                void Use() const;

                template <typename T>
                void InitializeUniform(const GLchar* uniformName, T defaultValue, const bool includeInApplyQueue = true)
                {
                    _uniformStorage->InitializeUniform<T>(uniformName, defaultValue, includeInApplyQueue);
                }

                template <typename T>
                void InitializeArrayUniform(const GLchar* uniformName, std::vector<T> defaultValue, const bool includeInApplyQueue = true)
                {
                    _uniformStorage->InitializeArrayUniform<T>(uniformName, defaultValue, includeInApplyQueue);
                }

                template <typename T>
                void InitializeSamplerUniform(const GLchar* uniformName, T defaultValue, const bool includeInApplyQueue = true)
                {
                    _uniformStorage->InitializeSamplerUniform<T>(uniformName, defaultValue, includeInApplyQueue);
                }

                template <typename T>
                void SetUniformInstantly(const GLchar* uniformName, T value) { _uniformStorage->SetUniformInstantly<T>(uniformName, value); }

                template <typename T>
                void SetArrayUniformInstantly(const GLchar* uniformName, T value) { _uniformStorage->SetArrayUniformInstantly<T>(uniformName, value); }

                template <typename T>
                void SetSamplerUniformInstantly(const GLchar* uniformName, T value) { _uniformStorage->SetSamplerUniformInstantly<T>(uniformName, value); }
            
                GLuint GetProgramID() const;

                void UniformStorageFromShader(const Shader* shader);

                UniformStorage* GetUniformStorage() const;
                UniformStorage* GetUniformStorageCopy() const;
        };
    }
}
