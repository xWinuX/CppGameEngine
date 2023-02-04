#pragma once

#include <map>
#include <iostream>
#include <vector>

#include "Uniform.h"
#include <glm/mat4x4.hpp>

#include "CubeMap.h"

#define UNIFORM(type, name, uniformType) \
typedef type name; \
typedef std::vector<type> ##name##V; \
std::map<int, UniformEntry<##uniformType##<##name##>>> _uniformEntries_##name; \

#define ARRAY_UNIFORM(type, nameBase, uniformType) \
typedef std::vector<type> nameBase##V; \
std::map<int, UniformEntry<##uniformType##<##nameBase##V>>> _uniformEntries_##nameBase##V; \


#define TRY_GET_LOCATION(codeIf) \
const int location = GetUniformLocation(uniformName); \
if (location < 0) { return nullptr; } \
codeIf

#define UNIFORM_SPECIALIZATION(type, uniformType) \
template <> \
inline Uniform<UniformStorage::##type##>* UniformStorage::GetUniformPtr<UniformStorage::##type##>(int location) { return &_uniformEntries_##type##[location].Uniform; } \
template <> \
inline Uniform<UniformStorage::##type##>* UniformStorage::GetUniformPtr<UniformStorage::##type##>(const std::string& uniformName) { TRY_GET_LOCATION(return GetUniformPtr<##type##>(location);) } \
template <> \
inline void UniformStorage::InitializeUniform<UniformStorage::##type##>(std::string uniformName, type defaultVar, const bool includeInApplyQueue, const bool resetAfterApply)  \
{ InitializeUniform<##type##, uniformType##<##type##>, &UniformStorage::_uniformEntries_##type##>(uniformName, defaultVar, includeInApplyQueue, resetAfterApply); }

#define ARRAY_UNIFORM_SPECIALIZATION(baseType, uniformType) \
template <> \
inline Uniform<UniformStorage::##baseType##>* UniformStorage::GetUniformPtr<UniformStorage::##baseType##>(int location) { return &_uniformEntries_##baseType##[location].Uniform; } \
template <> \
inline Uniform<UniformStorage::##baseType##>* UniformStorage::GetUniformPtr<UniformStorage::##baseType##>(const std::string& uniformName) { TRY_GET_LOCATION(return GetUniformPtr<##baseType##>(location);) } \
template <> \
inline void UniformStorage::InitializeUniform<UniformStorage::##baseType##>(std::string uniformName, baseType defaultVar, const bool includeInApplyQueue, const bool resetAfterApply)  \
{ InitializeUniform<##baseType##, uniformType##<##baseType##>, &UniformStorage::_uniformEntries_##baseType##>(uniformName, defaultVar, includeInApplyQueue, resetAfterApply); }


//std::map<int, UniformEntry<Array##uniformType##<std::vector<##type##>>>> _uniformEntries_##name##V; 

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
                        T Uniform;
                        bool     ApplyInQueue;
                        bool     ResetAfterApply;
                };


                UNIFORM(int, Int, Uniform)
                ARRAY_UNIFORM(int, Int, ArrayUniform)
            
                UNIFORM(float, Float, Uniform)
                ARRAY_UNIFORM(float, Float, ArrayUniform)
            
                UNIFORM(glm::vec4, Vec4, Uniform)
                ARRAY_UNIFORM(glm::vec4, Vec4, ArrayUniform)
            
                UNIFORM(glm::vec3, Vec3, Uniform)
                ARRAY_UNIFORM(glm::vec3, Vec3, ArrayUniform)

                UNIFORM(glm::vec2, Vec2, Uniform)
                ARRAY_UNIFORM(glm::vec2, Vec2, ArrayUniform)

                UNIFORM(glm::mat4, Mat4, Uniform)
                ARRAY_UNIFORM(glm::mat4, Mat4, ArrayUniform)
          
                UNIFORM(Texture*, TexturePtr, SamplerUniform)
                UNIFORM(CubeMap*, CubeMapPtr, SamplerUniform)

                GLuint                          _programID;
                std::map<std::string, int>      _uniformNameLocationMap;
                std::map<int, std::vector<int>> _applyQueue;
                bool                            _isTemplate              = false;
                unsigned int                    _invalidLocationsCounter = 0;

                template <typename T, typename TUniform, std::map<int, UniformEntry<TUniform>> UniformStorage::*MapPtr>
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
                    (this->*MapPtr).emplace(location, UniformEntry<TUniform>{TUniform{uniformName, location, defaultVar}, includeInApplyQueue, resetAfterApply});

                    if (location < 0 && !_isTemplate) { Debug::Log::Error("Something went wrong initializing uniform \"" + std::string(uniformName)); }
                }

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
                    ShowUniformNotSupportedError<T>();
                }

                template <typename T>
                Uniform<T>* GetUniformPtr(const std::string& uniformName) { ShowUniformNotSupportedError<T>(); }

                template <typename T>
                Uniform<T>* GetUniformPtr(int location) { ShowUniformNotSupportedError<T>(); }
        };


        UNIFORM_SPECIALIZATION(Int, Uniform)
        UNIFORM_SPECIALIZATION(Float, Uniform)
        UNIFORM_SPECIALIZATION(Vec3, Uniform)
        UNIFORM_SPECIALIZATION(Vec4, Uniform)
        UNIFORM_SPECIALIZATION(Mat4, Uniform)

        
        UNIFORM_SPECIALIZATION(TexturePtr, SamplerUniform)
        UNIFORM_SPECIALIZATION(CubeMapPtr, SamplerUniform)

        UNIFORM_SPECIALIZATION(IntV, ArrayUniform)
        UNIFORM_SPECIALIZATION(FloatV, ArrayUniform)
        UNIFORM_SPECIALIZATION(Vec3V, ArrayUniform)
        UNIFORM_SPECIALIZATION(Vec4V, ArrayUniform)
        UNIFORM_SPECIALIZATION(Mat4V, ArrayUniform)
    }
}
