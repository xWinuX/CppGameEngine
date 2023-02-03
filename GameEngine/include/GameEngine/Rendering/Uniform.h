#pragma once

#include "../Debug/Log.h"
#include "glad/glad.h"
#include <glm/mat4x4.hpp>

#include "CubeMap.h"
#include "Texture.h"
#include "glm/gtc/type_ptr.hpp"

#define LOCATION_CHECK if (this->GetLocation() < 0) { Debug::Log::Message(std::string(this->GetName()) + "'s location not found"); return; }

#define LOCATION_CHECK_ARRAY \
LOCATION_CHECK \
if (_value.empty()) { return; }

namespace GameEngine
{
    namespace Rendering
    {
        template <typename T>
        class Uniform
        {
            protected:
                const std::string _name;
                const GLint       _location = -1;
                const T           _defaultValue;
                T                 _value;

            public:
                Uniform():
                    _defaultValue(),
                    _value() {}

                Uniform(const std::string uniformName, const GLint location, T defaultValue):
                    _name(uniformName),
                    _location(location),
                    _defaultValue(defaultValue),
                    _value(defaultValue) { }


                void Apply() { Debug::Log::Message("This should never appear"); }

                void Set(T value) { _value = value; }

                void Reset() { _value = _defaultValue; }

                std::string GetName() const { return _name; }
                GLint       GetLocation() { return _location; }

                T GetDefaultValue() { return _defaultValue; }

                T* GetValuePtr() { return &_value; }
        };

        template <typename T>
        class SamplerUniform : public Uniform<T>
        {
            private:
                int _previousSlot = 0;

            public:
                SamplerUniform():
                    Uniform<T>() {}

                SamplerUniform(const std::string& uniformName, GLint location, T defaultValue):
                    Uniform<T>(uniformName, location, defaultValue) {}

                virtual void Apply(int slot = -1)
                {
                    LOCATION_CHECK
                    if (slot == -1) { slot = _previousSlot; }
                    this->_value->Bind(slot);
                    glUniform1i(this->_location, slot);
                    _previousSlot = slot;
                }
        };

        template <typename T>
        class ArrayUniform : public Uniform<T>
        {
            protected:
                size_t _maxSize = 0;

            public:
                ArrayUniform():
                    Uniform<T>() {}

                ArrayUniform(const std::string& uniformName, GLint location, T defaultValue):
                    Uniform<T>(uniformName, location, defaultValue),
                    _maxSize(defaultValue.size()) {}

                void Set(T value, size_t index)
                {
                    if (index >= _maxSize)
                    {
                        Debug::Log::Error("Uniform " + _name + " array index out of range!");
                        return;
                    }

                    this->_value[index] = value;
                }
        };

        template <typename T>
        class ArraySamplerUniform final : public SamplerUniform<T>, public ArrayUniform<T>
        {
            private:
                std::vector<int> _slotIndices;

            public:
                ArraySamplerUniform():
                    Uniform<T>() {}

                ArraySamplerUniform(const std::string& uniformName, GLint location, T defaultValue):
                    SamplerUniform<T>(uniformName, location, defaultValue),
                    ArrayUniform<T>(uniformName, location, defaultValue),
                    _slotIndices(std::vector<int>(defaultValue.size())) {}

            private:
                void Apply(int slot = -1) override
                {
                    LOCATION_CHECK
                    if (slot == -1) { slot = this->_previousSlot; }
                    for (size_t i = 0; i < this->_value.size(); i++)
                    {
                        this->_value->Bind(slot + i);
                        _slotIndices[i] = slot + i;
                    }
                    glUniform1iv(this->_location, _slotIndices.size(), _slotIndices.data());
                    this->_previousSlot = slot;
                }
        };


        template <>
        inline void Uniform<std::vector<int>>::Apply()
        {
            LOCATION_CHECK_ARRAY
            glUniform1iv(_location, static_cast<GLsizei>(_value.size()), _value.data());
        }

        template <>
        inline void Uniform<std::vector<float>>::Apply()
        {
            LOCATION_CHECK_ARRAY
            glUniform1fv(_location, static_cast<GLsizei>(_value.size()), _value.data());
        }

        template <>
        inline void Uniform<std::vector<glm::vec2>>::Apply()
        {
            LOCATION_CHECK_ARRAY
            glUniform2fv(_location, static_cast<GLsizei>(_value.size()), reinterpret_cast<GLfloat*>(_value.data()));
        }

        template <>
        inline void Uniform<std::vector<glm::vec3>>::Apply()
        {
            LOCATION_CHECK_ARRAY
            glUniform3fv(_location, static_cast<GLsizei>(_value.size()), reinterpret_cast<GLfloat*>(_value.data()));
        }

        template <>
        inline void Uniform<std::vector<glm::vec4>>::Apply()
        {
            LOCATION_CHECK_ARRAY
            glUniform4fv(_location, static_cast<GLsizei>(_value.size()), reinterpret_cast<GLfloat*>(_value.data()));
        }

        template <>
        inline void Uniform<int>::Apply()
        {
            LOCATION_CHECK
            glUniform1i(_location, _value);
        }

        template <>
        inline void Uniform<float>::Apply()
        {
            LOCATION_CHECK
            glUniform1f(_location, _value);
        }

        template <>
        inline void Uniform<glm::vec4>::Apply()
        {
            LOCATION_CHECK
            glUniform4f(_location, _value.x, _value.y, _value.z, _value.w);
        }

        template <>
        inline void Uniform<glm::vec3>::Apply()
        {
            LOCATION_CHECK
            glUniform3f(_location, _value.x, _value.y, _value.z);
        }

        template <>
        inline void Uniform<glm::mat4>::Apply()
        {
            LOCATION_CHECK
            glUniformMatrix4fv(_location, 1, GL_FALSE, glm::value_ptr(_value));
        }
    }
}
