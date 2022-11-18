#pragma once
#include <iostream>
#include <map>
#include <glad/glad.h>

#include "../Math/Vector4.h"

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
        static GLuint              CreateProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID);
        static ShaderProgramSource ParseShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    public:
        Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
        ~Shader();

        static void SetUniform4F(int uniformLocation, Vector4 vector4);

        void Use() const;
        void InitializeUniform4F(const GLchar* uniformName);
        void SetUniform4F(const GLchar* uniformName, Vector4 vector4) const;
        int  GetUniformLocation(const GLchar* uniformName);
};
