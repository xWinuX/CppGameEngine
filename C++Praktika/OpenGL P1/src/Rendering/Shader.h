#pragma once
#include <iostream>

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
};
