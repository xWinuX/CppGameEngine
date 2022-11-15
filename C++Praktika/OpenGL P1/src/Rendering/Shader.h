#pragma once
#include <iostream>

class Shader
{
    private:
        int        _programID;
        static int CompileShader(const std::string& shaderSource, int type);
        static int CreateProgram(int vertexShaderID, int fragmentShaderID);
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
