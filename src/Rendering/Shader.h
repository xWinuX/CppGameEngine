#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>


#include "Uniform.h"
#include "../Debug/Log.h"

class Shader
{
    private:
        struct ShaderProgramSource
        {
            std::string VertexSource;
            std::string FragmentSource;
        };

        GLuint                       _programID;
        std::map<const GLchar*, int> _uniformNameLocationMap;
        std::vector<int>             _uniformLocations;

        static GLuint              CompileShader(const std::string& shaderSource, int type);
        static ShaderProgramSource ParseShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    
        std::map<int, Uniform<glm::vec4>> _uniform4Fs;
        std::map<int, Uniform<glm::mat4>> _uniformMat4Fs;
        std::map<int, Uniform<int>>       _uniform1Is;

        GLuint CreateProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID);

        template <typename T>
        void InitializeUniform(const GLchar* uniformName, std::map<int, T>& defaultMap, T defaultVar)
        {
            const int location = glGetUniformLocation(_programID, uniformName);
            if (location != -1)
            {
                _uniformNameLocationMap[uniformName] = location;
                _uniformLocations.push_back(location);
                defaultMap[location] = defaultVar;
            }
            else { std::cout << "Something went wrong initializing uniform \"" << uniformName << "\"" << std::endl; }
        }

    public:
        Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
        ~Shader();

        int GetUniformLocation(const GLchar* uniformName);

        static void SetUniform4F(int uniformLocation, glm::vec4 vector4);
        static void SetUniformMat4F(int uniformLocation, glm::mat4x4 mat4);
        static void SetUniformI1(int uniformLocation, int i);

        void SetUniform4F(const GLchar* uniformName, glm::vec4 vector4) const;
        void SetUniformMat4F(const GLchar* uniformName, glm::mat4x4 mat4) const;
        void SetUniformI1(const GLchar* uniformName, int i);

        void InitializeUniformF4(const GLchar* uniformName, glm::vec4 defaultValue);
        void InitializeUniformMat4F(const GLchar* uniformName, glm::mat4 defaultValue);
        void InitializeUniformI1(const GLchar* uniformName, int defaultValue);

        void SetViewProjectionMatrix(const glm::mat4 viewProjection) const;
        void SetTransformMatrix(const glm::mat4 transformMatrix) const;

        void Use() const;
    
        std::vector<int>& GetUniformLocations() { return _uniformLocations; }
};
