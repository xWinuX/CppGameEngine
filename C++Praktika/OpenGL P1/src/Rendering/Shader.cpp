#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    const ShaderProgramSource source = ParseShader(vertexShaderFilePath, fragmentShaderFilePath);

    const GLuint vertexShader   = CompileShader(source.VertexSource, GL_VERTEX_SHADER);
    const GLuint fragmentShader = CompileShader(source.FragmentSource, GL_FRAGMENT_SHADER);

    _programID = CreateProgram(vertexShader, fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(_programID);
}

Shader::ShaderProgramSource Shader::ParseShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    int               i = 0;
    std::string       line;
    std::stringstream ss[2];
    for (const std::string& element : {vertexShaderPath, fragmentShaderPath})
    {
        std::ifstream stream(element);
        while (getline(stream, line)) { ss[i] << line << '\n'; }
        i++;
    }

    return {ss[0].str(), ss[1].str()};
}

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

unsigned int Shader::CreateProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID)
{
    // Attach shaders and link them
    const unsigned int shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    // Check for linking errors
    int success;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
        std::cout << " Exception: Program linking failed.\\n" << infoLog << std::endl;
    }

    // Free allocated memory for shaders
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    Use();
    InitializeUniform("u_ViewProjection");

    return shaderProgramID;
}

void Shader::Use() const
{
    glUseProgram(_programID);
}

void Shader::InitializeUniform(const GLchar* uniformName)
{
    const int location = glGetUniformLocation(_programID, uniformName);
    if (location != -1) { _uniformLocation[uniformName] = location; }
    else { std::cout << "Something went wrong initializing uniform \"" << uniformName << "\"" << std::endl; }
}

void Shader::SetViewProjectionMatrix(const glm::mat4 viewProjection) const
{
    if (_uniformLocation.find("u_ViewProjection") != _uniformLocation.end()) { SetUniformMat4F(_uniformLocation.at("u_ViewProjection"), viewProjection); }
}

void Shader::SetUniform4F(const GLchar* uniformName, const glm::vec4 vector4) const
{
    if (_uniformLocation.find(uniformName) != _uniformLocation.end()) { SetUniform4F(_uniformLocation.at(uniformName), vector4); }
}

void Shader::SetUniformMat4F(const GLchar* uniformName, const glm::mat4x4 mat4) const
{
    if (_uniformLocation.find(uniformName) != _uniformLocation.end()) { SetUniformMat4F(_uniformLocation.at(uniformName), mat4); }
}

void Shader::SetUniform4F(const int uniformLocation, const glm::vec4 vector4)
{
    glUniform4f(uniformLocation, vector4.x, vector4.y, vector4.z, vector4.w);
}

void Shader::SetUniformMat4F(const int uniformLocation, glm::mat4x4 mat4)
{
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat4[0][0]);
}

int Shader::GetUniformLocation(const GLchar* uniformName) { return _uniformLocation[uniformName]; }
