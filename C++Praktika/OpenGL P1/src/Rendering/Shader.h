#pragma once
#include <iostream>
#include <map>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

class Shader
{
    private:
        struct ShaderProgramSource
        {
            std::string VertexSource;
            std::string FragmentSource;
        };

        GLuint                       _programID;
        std::map<const GLchar*, int> _uniformLocation;

        static GLuint              CompileShader(const std::string& shaderSource, int type);
        static ShaderProgramSource ParseShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        GLuint CreateProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID);
    public:
        Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
        ~Shader();

        static void SetUniform4F(int uniformLocation, glm::vec4 vector4);
        static void SetUniformMat4F(int uniformLocation, glm::mat4x4 mat4);

        void Use() const;
        void InitializeUniform(const GLchar* uniformName);
        void SetViewProjectionMatrix(const glm::mat4 viewProjection) const;
        void SetUniform4F(const GLchar* uniformName, glm::vec4 vector4) const;
        void SetUniformMat4F(const GLchar* uniformName, glm::mat4x4 mat4) const;
        int  GetUniformLocation(const GLchar* uniformName);
};
