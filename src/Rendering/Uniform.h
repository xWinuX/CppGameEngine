#pragma once

#include "../Debug/Log.h"
#include "glad/glad.h"
#include <glm/mat4x4.hpp>

#include "Texture.h"

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
            _value(defaultValue) { }
    
        // ReSharper disable once CppMemberFunctionMayBeStatic (No it's not...)
        void Apply() { Debug::Log::Message("This should never appear"); }

        void Set(T value) { _value = value; }

        void Reset() { _value = _defaultValue; }
};


template <>
class Uniform<Texture*>
{
    private:
        const GLchar*  _name     = "";
        const GLint    _location = -1;
        const Texture* _defaultValue;
        const Texture* _value;
    public:
        Uniform():
            _defaultValue(),
            _value() { }

        Uniform(const GLchar* uniformName, const GLint location, const Texture* defaultValue):
            _name(uniformName),
            _location(location),
            _defaultValue(defaultValue),
            _value(defaultValue) { }
    
        // ReSharper disable once CppMemberFunctionMayBeStatic (No it's not...)
        void Apply(const int slot=0) const
        {
            _value->Bind(slot);
            glUniform1i(_location, slot);
        }

        void Set(const Texture* value) { _value = value; }

        void Reset() { _value = _defaultValue; }
};

template <>
inline void Uniform<std::vector<float>*>::Apply()
{
    glUniform1fv(_location, _value->size(), _value->data());
}

template <>
inline void Uniform<glm::vec4>::Apply()
{
    glUniform4f(_location, _value.x, _value.y, _value.z, _value.w);
}


template <>
inline void Uniform<std::vector<glm::vec4>*>::Apply()
{
    if (_value == nullptr) { return; }
    
    glUniform4fv(_location, _value->size()*4, reinterpret_cast<GLfloat*>(_value->data()));
}

template <>
inline void Uniform<glm::vec3>::Apply()
{
    glUniform3f(_location, _value.x, _value.y, _value.z);
}

template <>
inline void Uniform<std::vector<glm::vec3>*>::Apply()
{
    if (_value == nullptr) { return; }
    
    glUniform3fv(_location, _value->size()*3, reinterpret_cast<GLfloat*>(_value->data()));
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
