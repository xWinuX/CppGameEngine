#pragma once

class Shader
{
    private:
        int _programID;
        static int CompileShader(const char* shaderSource, int type);
        static int CreateProgram(int vertexShaderID, int fragmentShaderID);
    public:
        Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
        void Use() const;
};
