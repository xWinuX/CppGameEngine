#pragma once

#include "../Debug/Log.h"
#include "glad/glad.h"
#include <glm/mat4x4.hpp>

#include "CubeMap.h"
#include "Texture.h"
#include "Sampler.h"
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
                const GLuint      _shaderProgramID;
                const std::string _name;
                const GLint       _location = -1;
                const T           _defaultValue;
                T                 _value;

            public:
                Uniform():
                    _defaultValue(),
                    _value() {}

                Uniform(const GLuint shaderProgramID, const std::string uniformName, const GLint location, T defaultValue):
                    _shaderProgramID(shaderProgramID),
                    _name(uniformName),
                    _location(location),
                    _defaultValue(defaultValue),
                    _value(defaultValue) { }

                /**
                 * \brief Applies the uniform to the shader program (Note that the shader has to be bound for this to work correctly)
                 */
                void Apply() { Debug::Log::Message("This should never appear"); }

                /**
                 * \brief Sets the uniform value (The Uniform is applied in the next render loop)
                 * \param value Value to set uniform to
                 */
                void Set(T value) { _value = value; }


                /**
                 * \brief Sets a value to the uniform and call apply right after (This should only really be used inside the render loop since the shader needs to be bound) 
                 * \param value Value to set
                 */
                void SetInstantly(T value)
                {
                    Set(value);
                    Apply();
                }
            
                /**
                 * \brief Resets the uniforms value to it's default one that was given during initialization 
                 */
                void Reset() { _value = _defaultValue; }

                /**
                 * \brief Gets the name of the uniform
                 * \return The name of the uniform
                 */
                std::string GetName() const { return _name; }

                /**
                 * \brief Gets the location
                 * \return Returns the location of the uniform inside the shader
                 */
                GLint GetLocation() const { return _location; }

                /**
                 * \brief Gets the default value
                 * \return The default value the uniform was initialized with
                 */
                T GetDefaultValue() { return _defaultValue; }

                /**
                 * \brief Gets the pointer to the value, modifying the value in the pointer is the same as calling the Set() function
                 * \return Return the pointer to the uniform value
                 */
                T* GetValuePtr() { return &_value; }
        };
        
        class SamplerUniform : public Uniform<Sampler*>
        {
            private:
                int _previousSlot = 0;

            public:
                SamplerUniform():
                    Uniform() {}

                SamplerUniform(const GLuint shaderProgramID, const std::string& uniformName, GLint location, Sampler* defaultValue):
                    Uniform(shaderProgramID, uniformName, location, defaultValue) {}

                /**
                 * \brief Binds the sampler and sets the uniform to its index
                 * \param slot Slot to bind the sampler to
                 */
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
        class ArrayUniform : public Uniform<std::vector<T>>
        {
            protected:
                size_t _maxSize = 0;

            public:
                ArrayUniform():
                    Uniform<std::vector<T>>() {}

                ArrayUniform(const GLuint shaderProgramID, const std::string& uniformName, GLint location, std::vector<T> defaultValue):
                    Uniform<std::vector<T>>(shaderProgramID, uniformName, location, defaultValue),
                    _maxSize(defaultValue.size()) {}

                /**
                 * \brief Sets value at given array index
                 * \param value Value to set
                 * \param index Index in array to set given value to
                 */
                void Set(T value, const size_t index)
                {
                    if (index >= _maxSize)
                    {
                        Debug::Log::Error("Uniform " + this->_name + " array index out of range!");
                        return;
                    }

                    this->_value[index] = value;
                }

                /**
                 * \brief Sets value at given array index
                 * \param value Value to set
                 * \param index Index in array to set given value to
                 */
                void SetInstantly(T value, const size_t index)
                {
                    Set(value, index);
                    this->Apply();
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
