#pragma once

#include <map>
#include <iostream>
#include <vector>

#include "../Uniform.h"
#include <glm/mat4x4.hpp>


#define UNIFORM(type, suffix) std::map<int,  UniformEntry<##type##>> _uniform##suffix##s;

#define ADD_UNIFORM_SLOT(type,suffix) \
    template<> \
    inline void UniformBuffer::InitializeUniform<type>(const GLchar* uniformName, const type value, const bool includeInApplyQueue) \
    {  \
        InitializeUniform<type, &UniformBuffer::_uniform##suffix##s>(uniformName, value, includeInApplyQueue); \
    } \
    template<> \
    inline void UniformBuffer::SetUniform<type>(const int uniformLocation, const type value) \
    { \
        _uniform##suffix##s[uniformLocation].Uniform.Set(value); \
    } \
    template<> \
    inline void UniformBuffer::SetUniform<type>(const GLchar* uniformName, const type value) \
    { \
        const int uniformLocation = GetUniformLocation(uniformName); \
        if (uniformLocation == -1) \
        { \
            Debug::Log::Error("Uniform " + std::string(uniformName) + " was not found! Did you forget to initialize it?"); \
            return; \
        } \
        SetUniform<type>(uniformLocation, value); \
    } \
    template<> \
    inline void UniformBuffer::SetUniformInstant<type>(const int uniformLocation, const type value) \
    { \
        _uniform##suffix##s[uniformLocation].Uniform.Set(value); \
        _uniform##suffix##s[uniformLocation].Uniform.Apply(); \
    } \
    template<> \
    inline void UniformBuffer::SetUniformInstant<type>(const GLchar* uniformName, const type value) \
    { \
        const int uniformLocation = GetUniformLocation(uniformName); \
        if (uniformLocation == -1) \
        { \
            Debug::Log::Error("Uniform " + std::string(uniformName) + " was not found! Did you forget to initialize it?"); \
            return; \
        } \
        SetUniformInstant<type>(uniformLocation, value); \
    }

class Shader;

class UniformBuffer
{
    friend Shader;
    
    private:
        template <typename T>
        struct UniformEntry
        {
            public:
                Uniform<T> Uniform;
                bool       ApplyInQueue;
        };

        GLuint                          _programID;
        std::map<const GLchar*, int>    _uniformNameLocationMap;
        std::map<int, std::vector<int>> _applyQueue;

        UNIFORM(glm::mat4, Mat4F)
        UNIFORM(glm::vec4, 4F)
        UNIFORM(int, 1I)

        template <typename T, std::map<int, UniformEntry<T>> UniformBuffer::*MapPtr>
        void InitializeUniform(const GLchar* uniformName, T defaultVar, bool includeInApplyQueue = true)
        {
            const int location = glGetUniformLocation(_programID, uniformName);
            if (location != -1)
            {
                _uniformNameLocationMap[uniformName] = location;
                (this->*MapPtr).emplace(location, UniformEntry<T>{Uniform<T>{uniformName, location, defaultVar}, includeInApplyQueue});
            }
            else { Debug::Log::Error("Something went wrong initializing uniform \"" + std::string(uniformName)); }
        }

        template <typename T>
        void InitializeUniform(const GLchar* uniformName, T defaultVar, bool includeInApplyQueue = true) { ShowUniformNotSupportedError<T>(); }

    public:
        explicit UniformBuffer(const GLuint programID);

        void Apply();
        int  GetUniformLocation(const GLchar* uniformName);

        template <typename T>
        static void ShowUniformNotSupportedError() { Debug::Log::Error("Uniform type " + std::string(typeid(T).name()) + " is not supported"); }

        template <typename T>
        void SetUniform(int location, T value) { ShowUniformNotSupportedError<T>(); }

        template <typename T>
        void SetUniform(const GLchar* location, T value) { ShowUniformNotSupportedError<T>(); }

        template <typename T>
        void SetUniformInstant(int location, T value) { ShowUniformNotSupportedError<T>(); }

        template <typename T>
        void SetUniformInstant(const GLchar* location, T value) { ShowUniformNotSupportedError<T>(); }
};

ADD_UNIFORM_SLOT(glm::mat4, Mat4F)
ADD_UNIFORM_SLOT(glm::vec4, 4F)
ADD_UNIFORM_SLOT(int, 1I)
