#pragma once
#include <iostream>
#include <glad/glad.h>

class Shader
{
    private:
        unsigned int        _programID;
        static unsigned int CompileShader(const std::string& shaderSource, int type);
        static unsigned int CreateProgram(int vertexShaderID, int fragmentShaderID);
        struct ShaderProgramSource
        {
            std::string vertexSource;
            std::string fragmentSource;
        };
        static ShaderProgramSource ParseShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    public:
        Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
        ~Shader();
        void Use() const;
        void SetUniform4F(const GLchar* uniformName, float f0, float f1, float f2, float f3) const;
};
