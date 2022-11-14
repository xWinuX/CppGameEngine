#include "Shader.h"
#include <iostream>
#include <glad/glad.h>

Shader::Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
{
    // TODO: implement file loading
    const char* vertexShaderSource = "#version 400 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 400 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    const int vertexShader   = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
    const int fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    _programID = CreateProgram(vertexShader, fragmentShader);
}

int Shader::CompileShader(const char* shaderSource, const int type)
{
    const int shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderSource, nullptr);
    glCompileShader(shaderID);

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

int Shader::CreateProgram(int vertexShaderID, int fragmentShaderID)
{
    const int shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    // Check for linking errors
    int success;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cout << " Exception: Program linking failed.\\n" << infoLog << std::endl;
    }

    // Free allocated memory for shaders
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return  shaderProgramID;
}

void Shader::Use() const
{
    glUseProgram(_programID);
}
