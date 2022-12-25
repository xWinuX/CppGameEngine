#pragma once

#include "../Debug/Log.h"
#include "glad/glad.h"
#include <glm/mat4x4.hpp>

template <typename T>
class Uniform
{
    private:
        const GLchar* _name     = "";
        const GLint   _location = -1;
        const T       _defaultValue;
        T             _value;
        int           _setCount;
    public:
        Uniform():
            _defaultValue(),
            _value()
        {
            Debug::Log::Message("asdasd");
        }

        Uniform(const GLuint programID, const GLchar* uniformName, const GLint location, T defaultValue):
            _name(uniformName),
            _location(location),
            _defaultValue(defaultValue),
            _value(_defaultValue)
        {
            Debug::Log::Message("asdasd");

        }

        Uniform(const Uniform& other)
            :
            _name(other._name),
            _location(other._location),
            _defaultValue(other._defaultValue),
            _value(other._value),
            _setCount(other._setCount)
        {
            Debug::Log::Message("Copy");
        }

        Uniform(Uniform&& other) noexcept
            :
            _name(other._name),
            _location(other._location),
            _defaultValue(std::move(other._defaultValue)),
            _value(std::move(other._value)),
            _setCount(other._setCount)
        {
            Debug::Log::Message("Copy");
        }

        Uniform& operator=(const Uniform& other)
        {
            if (this == &other) return *this;
            _name         = other._name;
            _location     = other._location;
            _defaultValue = other._defaultValue;
            _value        = other._value;
            _setCount     = other._setCount;
            return *this;
        }

        Uniform& operator=(Uniform&& other) noexcept
        {
            if (this == &other) return *this;
            _name         = other._name;
            _location     = other._location;
            _defaultValue = std::move(other._defaultValue);
            _value        = std::move(other._value);
            _setCount     = other._setCount;
            return *this;
        }

        // ReSharper disable once CppMemberFunctionMayBeStatic (No it's not...)
        void Apply()  {  }

        void Set(T value)
        {
            _value = value;
            _setCount += 1;
        }

        void Reset() { _value = _defaultValue; }
};


template<>
inline void Uniform<glm::vec4>::Apply() 
{
    glUniform4f(_location, _value.x, _value.y, _value.z, _value.w);
}

template<>
inline void Uniform<glm::mat4>::Apply() 
{
    Debug::Log::Message(std::to_string(_setCount));
    _setCount += 1;
    glUniformMatrix4fv(_location, 1, GL_FALSE, &_value[0][0]);
}

template<>
inline void Uniform<int>::Apply() 
{
    glUniform1i(_location, _value);
}
