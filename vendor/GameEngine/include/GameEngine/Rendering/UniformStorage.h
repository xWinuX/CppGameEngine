#pragma once

#include <map>
#include <iostream>
#include <vector>

#include "Uniform.h"
#include <glm/mat4x4.hpp>

#include "CubeMap.h"
#include "Texture2DArray.h"

#define UNIFORM(type, suffix) std::map<int,  UniformEntry<##type##>> _uniform##suffix##s;

#define ADD_UNIFORM_SPECIALIZATION(type,suffix) \
        template<> \
        inline void UniformStorage::InitializeUniform<type>(std::string uniformName, type value, const bool includeInApplyQueue, const bool resetAfterApply) \
        {  \
            InitializeUniform<type, &UniformStorage::_uniform##suffix##s>(uniformName, value, includeInApplyQueue, resetAfterApply); \
        } \
        template<> \
        inline void UniformStorage::SetUniform<type>(const int uniformLocation, type value) \
        { \
            _uniform##suffix##s[uniformLocation].Uniform.Set(value); \
        } \
        template<> \
        inline void UniformStorage::SetUniform<type>(std::string uniformName, type value) \
        { \
            const int uniformLocation = GetUniformLocation(uniformName); \
            if (uniformLocation < 0) { return; } \
            SetUniform<type>(uniformLocation, value); \
        } \
        template<> \
        inline Uniform<type>* UniformStorage::GetUniformPtr<type>(std::string uniformName) \
        { \
            const int uniformLocation = GetUniformLocation(uniformName); \
            if (uniformLocation < 0) { return nullptr; } \
            return &_uniform##suffix##s[uniformLocation].Uniform; \
        } \
        template<> \
        inline void UniformStorage::SetUniformInstant<type>(const int uniformLocation, type value) \
        { \
            _uniform##suffix##s[uniformLocation].Uniform.Set(value); \
            _uniform##suffix##s[uniformLocation].Uniform.Apply(); \
        } \
        template<> \
        inline void UniformStorage::SetUniformInstant<type>(std::string uniformName, type value) \
        { \
            const int uniformLocation = GetUniformLocation(uniformName); \
            if (uniformLocation < 0) { return; } \
            SetUniformInstant<type>(uniformLocation, value); \
        }


namespace GameEngine
{
    namespace Rendering
    {
        class Shader;

        class UniformStorage
        {
            friend Shader;

            public:
                explicit UniformStorage();
                explicit UniformStorage(const GLuint programID);

                void DrawProperties(const std::string& fieldIdentifier);
                void Apply();

                int GetUniformLocation(const std::string& uniformName);

                UniformStorage* Copy(const GLuint programID) const;
                void            CopyTo(UniformStorage* uniformStorage) const;
                void            CopyFrom(const UniformStorage* uniformStorage);

                template <typename T>
                static void ShowUniformNotSupportedError() { Debug::Log::Error("Uniform type " + std::string(typeid(T).name()) + " is not supported"); }

                template <typename T>
                void InitializeUniform(std::string uniformName, T defaultVar, const bool includeInApplyQueue = true, const bool resetAfterApply = false)
                {
                    ShowUniformNotSupportedError<T>();
                }

                template <typename T>
                Uniform<T>* GetUniformPtr(std::string uniformName)
                {
                    ShowUniformNotSupportedError<T>();
                    return nullptr;
                }

                /**
                * \brief Sets uniform and will apply it in the next apply run
                * \tparam T Type of uniform
                * \param location Location of uniform
                * \param value Value to set uniform to
                */
                template <typename T>
                void SetUniform(int location, T value) { ShowUniformNotSupportedError<T>(); }

                /**
                 * \brief Sets uniform and will apply it in the next apply run
                 * \tparam T Type of uniform
                 * \param uniformName Name of uniform
                 * \param value Value to set uniform to
                 */
                template <typename T>
                void SetUniform(std::string uniformName, T value) { ShowUniformNotSupportedError<T>(); }

                /**
                 * \brief Sets uniform and applies it instantly
                 * \tparam T Type of uniform
                 * \param location Location of uniform
                 * \param value Value to set uniform to
                 */
                template <typename T>
                void SetUniformInstant(int location, T value) { ShowUniformNotSupportedError<T>(); }

                /**
                 * \brief Sets uniform and applies it instantly
                 * \tparam T Type of uniform
                 * \param uniformName Name of uniform
                 * \param value Value to set uniform to
                 */
                template <typename T>
                void SetUniformInstant(std::string uniformName, T value) { ShowUniformNotSupportedError<T>(); }

            private:
                template <typename T>
                struct UniformEntry
                {
                    public:
                        Uniform<T> Uniform;
                        bool       ApplyInQueue;
                        bool       ResetAfterApply;
                };

                GLuint                          _programID;
                std::map<std::string, int>      _uniformNameLocationMap;
                std::map<int, std::vector<int>> _applyQueue;
                bool                            _isTemplate              = false;
                unsigned int                    _invalidLocationsCounter = 0;

                UNIFORM(glm::mat4, Mat4F)
                UNIFORM(glm::vec4, 4F)
                UNIFORM(std::vector<glm::vec4>*, 4FV)
                UNIFORM(glm::vec3, 3F)
                UNIFORM(std::vector<glm::vec3>*, 3FV)
                UNIFORM(int, 1I)
                UNIFORM(float, 1F)
                UNIFORM(std::vector<float>*, 1FV)
                UNIFORM(Texture2D*, Texture2D)
                UNIFORM(Texture2DArray*, Texture2DArray)
                UNIFORM(CubeMap*, CubeMap)

                template <typename T, std::map<int, UniformEntry<T>> UniformStorage::*MapPtr>
                void InitializeUniform(std::string uniformName, T defaultVar, const bool includeInApplyQueue = true, const bool resetAfterApply = false)
                {
                    int location = 0;

                    if (_isTemplate)
                    {
                        location -= _invalidLocationsCounter;
                        _invalidLocationsCounter++;
                    }
                    else
                    {
                        location = glGetUniformLocation(_programID, uniformName.c_str());

                        if (location == -1)
                        {
                            location -= _invalidLocationsCounter;
                            _invalidLocationsCounter++;
                            Debug::Log::Message(std::to_string(_invalidLocationsCounter));
                        }
                    }

                    _uniformNameLocationMap[uniformName] = location;
                    (this->*MapPtr).emplace(location, UniformEntry<T>{Uniform<T>{uniformName, location, defaultVar}, includeInApplyQueue, resetAfterApply});

                    if (location < 0 && !_isTemplate) { Debug::Log::Error("Something went wrong initializing uniform \"" + std::string(uniformName)); }
                }
        };

        ADD_UNIFORM_SPECIALIZATION(Texture2D*, Texture2D)
        ADD_UNIFORM_SPECIALIZATION(Texture2DArray*, Texture2DArray)
        ADD_UNIFORM_SPECIALIZATION(CubeMap*, CubeMap)
        ADD_UNIFORM_SPECIALIZATION(glm::mat4, Mat4F)
        ADD_UNIFORM_SPECIALIZATION(glm::vec4, 4F)
        ADD_UNIFORM_SPECIALIZATION(std::vector<glm::vec4>*, 4FV)
        ADD_UNIFORM_SPECIALIZATION(glm::vec3, 3F)
        ADD_UNIFORM_SPECIALIZATION(std::vector<glm::vec3>*, 3FV)
        ADD_UNIFORM_SPECIALIZATION(float, 1F)
        ADD_UNIFORM_SPECIALIZATION(std::vector<float>*, 1FV)
        ADD_UNIFORM_SPECIALIZATION(int, 1I)
    }
}
