﻿#pragma once

#include "../Debug/Log.h"
#include "glad/glad.h"
#include <glm/mat4x4.hpp>

#include "Texture.h"
#include "glm/gtc/type_ptr.hpp"

#define LOCATION_CHECK if (_location < 0) { Debug::Log::Message(std::string(_name) + "'s location not found"); return; }

namespace GameEngine
{
    namespace Rendering
    {
        template <typename T>
        class Uniform
        {
            private:
                const std::string _name;
                const GLint       _location = -1;
                const T           _defaultValue;
                T                 _value;

            public:
                Uniform():
                    _defaultValue(),
                    _value() { }

                Uniform(const std::string uniformName, const GLint location, T defaultValue):
                    _name(uniformName),
                    _location(location),
                    _defaultValue(defaultValue),
                    _value(defaultValue)
                {
                    Debug::Log::Message(_name);
                    Debug::Log::Message(std::to_string(_location));
                }

                // ReSharper disable once CppMemberFunctionMayBeStatic (No it's not...)
                void Apply() { Debug::Log::Message("This should never appear"); }

                void Set(T value) { _value = value; }

                void Reset() { _value = _defaultValue; }

                std::string GetName() const { return _name; }
                T           GetDefaultValue() { return _defaultValue; }
        };


        template <>
        class Uniform<Texture*>
        {
            private:
                const std::string _name;
                const GLint       _location = -1;
                const Texture*    _defaultValue;
                const Texture*    _value;

            public:
                Uniform():
                    _defaultValue(),
                    _value() { }

                Uniform(const std::string uniformName, const GLint location, const Texture* defaultValue):
                    _name(uniformName),
                    _location(location),
                    _defaultValue(defaultValue),
                    _value(defaultValue) { }

                void Apply(const int slot = 0) const
                {
                    LOCATION_CHECK
                    _value->Bind(slot);
                    glUniform1i(_location, slot);
                }

                void Set(const Texture* value) { _value = value; }

                void        Reset() { _value = _defaultValue; }
                std::string GetName() const { return _name; }
                Texture*    GetDefaultValue() const { return const_cast<Texture*>(_defaultValue); }
        };

        template <>
        inline void Uniform<float>::Apply()
        {
            LOCATION_CHECK
            glUniform1f(_location, _value);
        }

        template <>
        inline void Uniform<std::vector<float>*>::Apply()
        {
            LOCATION_CHECK
            glUniform1fv(_location, static_cast<int>(_value->size()), _value->data());
        }

        template <>
        inline void Uniform<glm::vec4>::Apply()
        {
            LOCATION_CHECK
            glUniform4f(_location, _value.x, _value.y, _value.z, _value.w);
        }

        template <>
        inline void Uniform<std::vector<glm::vec4>*>::Apply()
        {
            LOCATION_CHECK
            if (_value == nullptr) { return; }

            glUniform4fv(_location, static_cast<int>(_value->size()), reinterpret_cast<GLfloat*>(_value->data()));
        }

        template <>
        inline void Uniform<glm::vec3>::Apply()
        {
            LOCATION_CHECK
            glUniform3f(_location, _value.x, _value.y, _value.z);
        }

        template <>
        inline void Uniform<std::vector<glm::vec3>*>::Apply()
        {
            LOCATION_CHECK
            if (_value == nullptr) { return; }

            glUniform3fv(_location, static_cast<int>(_value->size()), reinterpret_cast<GLfloat*>(_value->data()));
        }

        template <>
        inline void Uniform<glm::mat4>::Apply()
        {
            LOCATION_CHECK
            glUniformMatrix4fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
        }

        template <>
        inline void Uniform<int>::Apply()
        {
            LOCATION_CHECK
            glUniform1i(_location, _value);
        }
    }
}