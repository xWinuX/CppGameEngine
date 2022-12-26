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
    public:
        Uniform():
            _defaultValue(),
            _value() { }

        Uniform(const GLchar* uniformName, const GLint location, T defaultValue):
            _name(uniformName),
            _location(location),
            _defaultValue(defaultValue),
            _value(_defaultValue) { }


        // ReSharper disable once CppMemberFunctionMayBeStatic (No it's not...)
        void Apply() { Debug::Log::Message("This should never appear"); }

        void Set(T value) { _value = value; }

        void Reset() { _value = _defaultValue; }
};


template <>
inline void Uniform<glm::vec4>::Apply()
{
    glUniform4f(_location, _value.x, _value.y, _value.z, _value.w);
}

template <>
inline void Uniform<glm::mat4>::Apply()
{
    glUniformMatrix4fv(_location, 1, GL_FALSE, &_value[0][0]);
}

template <>
inline void Uniform<int>::Apply()
{
    glUniform1i(_location, _value);
}
