#pragma once

#include <functional>
#include <map>
#include <vector>
#include <iostream>


#include "Uniform.h"
#include <glm/mat4x4.hpp>

#define ADD_UNIFORM_SLOT(type,suffix) \
private: \
        std::map<int,  Uniform<##type##>> _uniform##suffix##s; \
public: \
    template<> \
    void InitializeUniform<type>(const GLchar* uniformName, type value) \
    {  \
        InitializeUniform<type, &UniformBuffer::_uniform##suffix##s>(uniformName, value); \
    } \
    template<> \
    void SetUniform<type>(const int uniformLocation, const type value) \
    { \
        _uniform##suffix##s[uniformLocation].Set(value); \
    } \
    template<> \
    void SetUniform<type>(const GLchar* uniformName, const type value) \
    { \
        int uniformLocation = GetUniformLocation(uniformName); \
        if (uniformLocation == -1) { return; } \
        SetUniform<type>(uniformLocation, value); \
    } \
    template<> \
    void SetUniformInstant<type>(const int uniformLocation, const type value) \
    { \
        _uniform##suffix##s[uniformLocation].Set(value); \
        _uniform##suffix##s[uniformLocation].Apply(); \
    } \
    template<> \
    void SetUniformInstant<type>(const GLchar* uniformName, const type value) \
    { \
        int uniformLocation = GetUniformLocation(uniformName); \
        if (uniformLocation == -1) { return; } \
        SetUniformInstant<type>(uniformLocation, value); \
    }

class UniformBuffer
{
    private:
        GLuint                       _programID;
        std::map<const GLchar*, int> _uniformNameLocationMap;

        template <typename T, std::map<int, Uniform<T>> UniformBuffer::*MapPtr>
        void InitializeUniform(const GLchar* uniformName, T defaultVar)
        {
            const int location = glGetUniformLocation(_programID, uniformName);
            if (location != -1)
            {
                _uniformNameLocationMap[uniformName] = location;
                (this->*MapPtr).emplace(location, Uniform<T>{_programID, uniformName, location, defaultVar});
            }
            else { Debug::Log::Error("Something went wrong initializing uniform \"" + std::string(uniformName)); }
        }

        template <typename T>
        void InitializeUniform(const GLchar* uniformName, T defaultVar) { ShowUniformNotSupportedError<T>(); }

    public:
        explicit UniformBuffer(const GLuint programID);
    
        void Apply();
        int  GetUniformLocation(const GLchar* uniformName);

        template <typename T>
        static void ShowUniformNotSupportedError() { Debug::Log::Error("Uniform type " + typeid(T).name() + " is not supported"); }

        template <typename T>
        void SetUniform(int location, T value) { ShowUniformNotSupportedError<T>(); }

        template <typename T>
        void SetUniform(const GLchar* location, T value) { ShowUniformNotSupportedError<T>(); }

        template <typename T>
        void SetUniformInstant(int location, T value) { ShowUniformNotSupportedError<T>(); }

        template <typename T>
        void SetUniformInstant(const GLchar* location, T value) { ShowUniformNotSupportedError<T>(); }

        ADD_UNIFORM_SLOT(glm::vec4, 4F)
        ADD_UNIFORM_SLOT(glm::mat4, Mat4F)
        ADD_UNIFORM_SLOT(int, 1I)
};
