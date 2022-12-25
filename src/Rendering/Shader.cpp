#include "Shader.h"
#include <iostream>
#include <fstream>

GLuint Shader::_currentlyBoundProgram = 999;

GLuint Shader::CompileShader(const std::string& shaderSource, const int type)
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

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource, const char* geometryShaderSource)
{
    _programID = glCreateProgram();

    // Vertex shader
    const std::string vertexShader   = Stream(vertexShaderSource).GetFileContent();
    const GLuint      vertexShaderID = CompileShader(vertexShader, GL_VERTEX_SHADER);
    glAttachShader(_programID, vertexShaderID);

    // Fragment shader
    const std::string fragmentShader   = Stream(fragmentShaderSource).GetFileContent();
    const GLuint      fragmentShaderID = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(_programID, fragmentShaderID);

    // Geometry shader
    if (geometryShaderSource != nullptr)
    {
        const std::string geometryShader   = Stream(geometryShaderSource).GetFileContent();
        const GLuint      geometryShaderID = CompileShader(geometryShader, GL_GEOMETRY_SHADER);
        glAttachShader(_programID, geometryShaderID);
    }

    // Link program
    glLinkProgram(_programID);

    // Check for linking errors
    int success;
    glGetProgramiv(_programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(_programID, 512, nullptr, infoLog);
        std::cout << " Exception: Program linking failed.\\n" << infoLog << std::endl;
    }

    // Free allocated memory for shaders
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    // Create uniform buffer
    _uniformBuffer = new UniformBuffer(_programID);
}

Shader::~Shader()
{
    glDeleteProgram(_programID);
    delete _uniformBuffer;
}

void Shader::Use() const
{
    glUseProgram(_programID);
}

GLuint         Shader::GetProgramID() const { return _programID; }
UniformBuffer* Shader::GetUniformBuffer() const { return _uniformBuffer; }

UniformBuffer* Shader::GetUniformBufferCopy() const
{
    Debug::Log::Message("COPY BUFFER");
    return _uniformBuffer;
}
