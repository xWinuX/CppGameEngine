#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
// ReSharper disable once CppUnusedIncludeDirective (needed for typeid().name)
#include <typeinfo>
#include <vector>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

#include "Uniform.h"
#include "../Debug/Log.h"
#include "../IO/Stream.h"


#define CREATE_UNIFORM_INITIALIZER(type,var)      \
template<> \
void InitializeUniform<type>(const GLchar* uniformName, type defaultVar) \
{  \
    InitializeUniform<type, &Shader<VertexShader, FragmentShader>::var>(uniformName, defaultVar); \
}


template <char*VertexShader, char*FragmentShader, char*GeometryShader = nullptr>
class Shader
{
    private:
        GLuint                       _programID;
        std::map<const GLchar*, int> _uniformNameLocationMap;
        std::vector<int>             _uniformLocations;

        std::map<int, const Uniform<glm::vec4>> _uniform4Fs;
        std::map<int, const Uniform<glm::mat4>> _uniformMat4Fs;
        std::map<int, const Uniform<int>>       _uniform1Is;

        static GLuint CompileShader(const std::string& shaderSource, int type)
        {
            // Create shader
            const GLuint shaderID      = glCreateShader(type);
            const char*  pShaderSource = shaderSource.c_str();

            // Bind shader source and compile
            glShaderSource(shaderID, 1, &pShaderSource, nullptr);
            glCompileShader(shaderID);

            // Check if compilation was successful
            int success;
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                char infoLog[512];
                glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
                std::cout << "Exception: Vertex shader compilation failed.\n" << infoLog << std::endl;
            }

            return shaderID;
        }
    
        void CreateProgram()
        {
            const unsigned int programID = glCreateProgram();

            // Vertex shader
            const std::string vertexShaderSource = Stream(VertexShader).GetFileContent();
            const GLuint      vertexShaderID     = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
            glAttachShader(programID, vertexShaderID);

            // Fragment shader
            const std::string fragmentShaderSource = Stream(FragmentShader).GetFileContent();
            const GLuint      fragmentShaderID     = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
            glAttachShader(programID, fragmentShaderID);

            // Geometry shader
            if (GeometryShader != nullptr)
            {
                std::string  geometryShaderSource = Stream(GeometryShader).GetFileContent();
                const GLuint geometryShaderID     = CompileShader(GeometryShader, GL_GEOMETRY_SHADER);
                glAttachShader(programID, geometryShaderID);
            }

            // Link program
            glLinkProgram(programID);

            // Check for linking errors
            int success;
            glGetProgramiv(programID, GL_LINK_STATUS, &success);
            if (!success)
            {
                char infoLog[512];
                glGetProgramInfoLog(programID, 512, nullptr, infoLog);
                std::cout << " Exception: Program linking failed.\\n" << infoLog << std::endl;
            }

            // Free allocated memory for shaders
            glDeleteShader(vertexShaderID);
            glDeleteShader(fragmentShaderID);

            _programID = programID;
        }

        template <typename T, std::map<int, const Uniform<T>> Shader::*MapPtr>
        void InitializeUniform(const GLchar* uniformName, T defaultVar)
        {
            const int location = glGetUniformLocation(_programID, uniformName);
            if (location != -1)
            {
                _uniformNameLocationMap[uniformName] = location;
                _uniformLocations.push_back(location);
                (*MapPtr)[location] = Uniform<T>(_programID, uniformName, defaultVar);
            }
            else { std::cout << "Something went wrong initializing uniform \"" << uniformName << "\"" << std::endl; }
        }

    public:
        Shader() { CreateProgram(); }

        ~Shader()
        {
            glDeleteProgram(_programID);
        }

        template <typename T>
        static void ShowUniformNotSupportedError() { Debug::Log::Error("Uniform type " + typeid(T).name() + " is not supported"); }

        template <typename T>
        void SetUniform(int uniformLocation, T value) { ShowUniformNotSupportedError<T>(); }

        template <typename T>
        void SetUniform(const GLchar* uniformName, T value)
        {
            if (_uniformNameLocationMap.find(uniformName) != _uniformNameLocationMap.end()) { SetUniform<T>(_uniformNameLocationMap.at(uniformName), value); }
        }

        template <typename T>
        void InitializeUniform(const GLchar* uniformName, T defaultVar) { ShowUniformNotSupportedError<T>(); }

        int GetUniformLocation(const GLchar* uniformName)
        {
            if (_uniformNameLocationMap.find(uniformName) == _uniformNameLocationMap.end()) { return -1; }
            return _uniformNameLocationMap[uniformName];
        }

        void Use() const
        {
            glUseProgram(_programID);
        }

        CREATE_UNIFORM_INITIALIZER(glm::vec4, _uniform4Fs)
        CREATE_UNIFORM_INITIALIZER(glm::mat4, _uniformMat4Fs)
        CREATE_UNIFORM_INITIALIZER(int, _uniform1Is)
};
