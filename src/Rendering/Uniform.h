#pragma once
#include <vcruntime_typeinfo.h>

#include "../Debug/Log.h"
#include "glad/glad.h"
#include <typeinfo>

template <typename T>
class Uniform
{
    private:
        const GLchar* _name;
        const T       _defaultValue;
        const GLint   _location;
        T             _value;
        bool          _isSet;
    public:
        Uniform(const GLuint programID, const GLchar* uniformName, T defaultValue):
            _name(uniformName),
            _defaultValue(defaultValue),
            _location(glGetUniformLocation(programID, uniformName)),
            _value(nullptr)
        {
        }

        void Apply() { Debug::Log::Error("Uniform type " + typeid(T).name() + " not supported"); }

        void Set(T value)
        {
            _value = value;
            _isSet = true;
        }

        void Reset() { _isSet = false; }
};
