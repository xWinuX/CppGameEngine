﻿#include "GameEngine/Rendering/Shader.h"

#include <fstream>
#include <iostream>
#include <glad/glad.h>

#include "GameEngine/Utils/String.h"

using namespace GameEngine::Rendering;
using namespace GameEngine::IO;
using namespace GameEngine::Utils;

const Shader* Shader::_currentActiveShader = nullptr;

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
        Debug::Log::Error(" Exception: shader compilation failed.\\n" + std::string(infoLog));
    }

    return shaderID;
}

std::string Shader::PreprocessShader(const std::string& shader) { return String::ReplaceIncludeMacros(shader); }

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource, const char* geometryShaderSource)
{
    Debug::Log::Message(std::string(vertexShaderSource)+"------------");
    
    _programID = glCreateProgram();

    // Vertex shader
    const std::string vertexShader   = PreprocessShader(vertexShaderSource);
    const GLuint      vertexShaderID = CompileShader(vertexShader, GL_VERTEX_SHADER);
    glAttachShader(_programID, vertexShaderID);

    // Fragment shader
    const std::string fragmentShader   = PreprocessShader(fragmentShaderSource);
    const GLuint      fragmentShaderID = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(_programID, fragmentShaderID);

    // Geometry shader
    if (geometryShaderSource != nullptr)
    {
        const std::string geometryShader   = PreprocessShader(geometryShaderSource);
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
        Debug::Log::Error(" Exception: Program linking failed.\\n" + std::string(infoLog));
    }

    // Free allocated memory for shaders
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    // Create uniform buffer
    _uniformStorage = new UniformStorage(_programID);
}

Shader::~Shader()
{
    glDeleteProgram(_programID);
    delete _uniformStorage;
}

void Shader::Use() const
{
    glUseProgram(_programID);
    _currentActiveShader = this;
}

const Shader* Shader::GetCurrentActiveShader() { return _currentActiveShader; }

void Shader::UniformStorageFromShader(const Shader* shader)
{
    delete _uniformStorage;
    _uniformStorage = shader->GetUniformStorage()->Copy(_programID);
}

GLuint Shader::GetProgramID() const { return _programID; }

UniformStorage* Shader::GetUniformStorage() const { return _uniformStorage; }
UniformStorage* Shader::GetUniformStorageCopy() const { return _uniformStorage->Copy(_programID); }
