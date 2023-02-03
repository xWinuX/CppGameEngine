﻿#pragma once

#include <map>
#include <iostream>
#include <vector>

#include "Uniform.h"
#include <glm/mat4x4.hpp>

#include "CubeMap.h"

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
                UNIFORM(std::vector<float>*, 1FV)
                UNIFORM(Texture*, Texture)
                UNIFORM(CubeMap*, CubeMap)

                template<typename T>
                std::map<int, UniformEntry<T>> _uniformEntries;
            
            public:
                explicit UniformStorage();
                explicit UniformStorage(const GLuint programID);

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
                    Debug::Log::Message("Initializing uniform " + uniformName);
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
                    _uniformEntries<T>.emplace(location, UniformEntry<T>{Uniform<T>{uniformName, location, defaultVar}, includeInApplyQueue, resetAfterApply});

                    if (location < 0 && !_isTemplate) { Debug::Log::Error("Something went wrong initializing uniform \"" + std::string(uniformName)); }
                }

                template <typename T>
                Uniform<T>* GetUniformPtr(std::string uniformName)
                {
                    return &_uniformEntries<T>[uniformName].Uniform;
                }

                template <typename T>
                void SetUniform(int location, T value)
                {
                    _uniformEntries<T>[location].Uniform.Set(value);
                }

                template <typename T>
                void SetUniform(const std::string uniformName, T value)
                {
                    const int uniformLocation = GetUniformLocation(uniformName); \
                    if (uniformLocation < 0) { return; }
                    SetUniform<T>(uniformLocation, value);
                }

                template <typename T>
                void SetUniformInstant(int location, T value)
                {
                    _uniformEntries<T>[location].Uniform.Set(value);
                    _uniformEntries<T>[location].Uniform.Apply();
                }

                template <typename T>
                void SetUniformInstant(std::string uniformName, T value) { ShowUniformNotSupportedError<T>(); }
        };

        ADD_UNIFORM_SPECIALIZATION(Texture*, Texture)
        ADD_UNIFORM_SPECIALIZATION(CubeMap*, CubeMap)
        ADD_UNIFORM_SPECIALIZATION(glm::mat4, Mat4F)
        ADD_UNIFORM_SPECIALIZATION(glm::vec4, 4F)
        ADD_UNIFORM_SPECIALIZATION(std::vector<glm::vec4>*, 4FV)
        ADD_UNIFORM_SPECIALIZATION(glm::vec3, 3F)
        ADD_UNIFORM_SPECIALIZATION(std::vector<glm::vec3>*, 3FV)

        template <>
        inline void UniformStorage::InitializeUniform<float>(std::string uniformName, float value, const bool includeInApplyQueue, const bool resetAfterApply)
        {
            InitializeUniform<float, &UniformStorage::_uniform1Fs>(uniformName, value, includeInApplyQueue, resetAfterApply);
        }

        template <>
        inline void UniformStorage::SetUniform<float>(const int uniformLocation, float value) { _uniform1Fs[uniformLocation].Uniform.Set(value); }

        template <>
        inline void UniformStorage::SetUniform<float>(std::string uniformName, float value)
        {
            const int uniformLocation = GetUniformLocation(uniformName);
            if (uniformLocation < 0) { return; }
            SetUniform<float>(uniformLocation, value);
        }

        template <>
        inline Uniform<float>* UniformStorage::GetUniformPtr<float>(std::string uniformName)
        {
            const int uniformLocation = GetUniformLocation(uniformName);
            if (uniformLocation < 0) { return nullptr; }
            return &_uniform1Fs[uniformLocation].Uniform;
        }

        template <>
        inline void UniformStorage::SetUniformInstant<float>(const int uniformLocation, float value)
        {
            _uniform1Fs[uniformLocation].Uniform.Set(value);
            _uniform1Fs[uniformLocation].Uniform.Apply();
        }

        template <>
        inline void UniformStorage::SetUniformInstant<float>(std::string uniformName, float value)
        {
            const int uniformLocation = GetUniformLocation(uniformName);
            if (uniformLocation < 0) { return; }
            SetUniformInstant<float>(uniformLocation, value);
        }

        ADD_UNIFORM_SPECIALIZATION(std::vector<float>*, 1FV)
        ADD_UNIFORM_SPECIALIZATION(int, 1I)
    }
}
