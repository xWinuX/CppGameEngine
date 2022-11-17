#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    const ShaderProgramSource source = ParseShader(vertexShaderFilePath, fragmentShaderFilePath);

    const int vertexShader   = CompileShader(source.vertexSource, GL_VERTEX_SHADER);
    const int fragmentShader = CompileShader(source.fragmentSource, GL_FRAGMENT_SHADER);

    _programID = CreateProgram(vertexShader, fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(_programID);
}

/**
 * \brief Parses given file sources into an easy to use struct
 * \param vertexShaderPath Path to the vertex shader file
 * \param fragmentShaderPath Path tot hte fragment shader file 
 * \return ShaderProgramSource struct containing the both sources
 */
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

unsigned int Shader::CompileShader(const std::string& shaderSource, const int type)
{
    // Create shader
    const unsigned int shaderID = glCreateShader(type);
    const char* pShaderSource = shaderSource.c_str();

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

unsigned int Shader::CreateProgram(const int vertexShaderID, const int fragmentShaderID)
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

    return shaderProgramID;
}

void Shader::Use() const
{
    glUseProgram(_programID);
}
