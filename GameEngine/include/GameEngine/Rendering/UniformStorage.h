#pragma once

#include <map>
#include <iostream>
#include <vector>

#include "Uniform.h"
#include <glm/mat4x4.hpp>

#include "CubeMap.h"

#define TRY_GET_LOCATION(codeIf) \
const int location = GetUniformLocation(uniformName); \
if (location < 0) { return nullptr; } \
codeIf

#define TRY_GET_LOCATION_NORET(codeIf) \
const int location = GetUniformLocation(uniformName); \
if (location < 0) { return; } \
codeIf

#define UNIFORM(type, name) \
typedef type name; \
std::map<int, UniformEntry<Uniform<type>>> _uniformEntries_##name;

#define SAMPLER_UNIFORM(type, name) \
typedef type name##Sampler; \
std::map<int, UniformEntry<SamplerUniform<type>>> _uniformEntries_##name##Sampler;

#define ARRAY_UNIFORM(baseType, nameBase) \
typedef std::vector<baseType> nameBase##V; \
std::map<int, UniformEntry<ArrayUniform<baseType>>> _uniformEntries_##nameBase##V;

/**
 * \brief Create a template specialization for a Uniform
 * \param name Name of type to use
 */
#define UNIFORM_INIT(name) \
template <> \
inline void UniformStorage::InitializeUniform<UniformStorage::name>(const std::string uniformName, name defaultValue, const bool includeInApplyQueue, const bool resetAfterApply) \
{ \
    const int location = AddUniform(uniformName); \
    InitializeUniform<##name##, &UniformStorage::_uniformEntries_##name##>(uniformName, location, defaultValue, includeInApplyQueue, resetAfterApply); \
} \
\
template<> inline Uniform<UniformStorage::name>* UniformStorage::GetUniform(const int location) { return &_uniformEntries_##name##[location].Uniform; } \
\
template<> inline Uniform<UniformStorage::name>* UniformStorage::GetUniform(const std::string& uniformName) { TRY_GET_LOCATION(return GetUniform<name>(location)); } \
\
template <> \
inline void UniformStorage::SetUniform<UniformStorage::name>(const int location, const name value) { _uniformEntries_##name##[location].Uniform.Set(value); } \
\
template <> \
inline void UniformStorage::SetUniform<UniformStorage::name>(const std::string& uniformName, const name value) { TRY_GET_LOCATION_NORET(SetUniform<name>(location, value);) } \
\
template <> \
inline void UniformStorage::SetUniformInstantly<UniformStorage::name>(const int location, const name value) { _uniformEntries_##name##[location].Uniform.SetInstantly(value); } \
\
template <> \
inline void UniformStorage::SetUniformInstantly<UniformStorage::name>(const std::string& uniformName, const name value) { TRY_GET_LOCATION_NORET(SetUniformInstantly<name>(location, value);) } \



/**
 * \brief Create a template specialization for a Sampler Uniform
 * \param name Name of type to use
 */
#define SAMPLER_UNIFORM_INIT(name) \
template <> \
inline void UniformStorage::InitializeSamplerUniform<UniformStorage::name>(const std::string uniformName, name defaultValue, const bool includeInApplyQueue, const bool resetAfterApply) \
{ \
    const int location = AddUniform(uniformName); \
    InitializeSamplerUniform<##name##, &UniformStorage::_uniformEntries_##name##>(uniformName, location, defaultValue, includeInApplyQueue, resetAfterApply); \
} \
\
template<> inline SamplerUniform<UniformStorage::name>* UniformStorage::GetSamplerUniform(const int location) { return &_uniformEntries_##name##[location].Uniform; } \
\
template<> inline SamplerUniform<UniformStorage::name>* UniformStorage::GetSamplerUniform(const std::string& uniformName) { TRY_GET_LOCATION(return GetSamplerUniform<name>(location)); } \
\
template <> \
inline void UniformStorage::SetSamplerUniform<UniformStorage::name>(const int location, const name value) { _uniformEntries_##name##[location].Uniform.Set(value); } \
\
template <> \
inline void UniformStorage::SetSamplerUniform<UniformStorage::name>(const std::string& uniformName, const name value) { TRY_GET_LOCATION_NORET(SetSamplerUniform<name>(location, value);) } \
\
template <> \
inline void UniformStorage::SetSamplerUniformInstantly<UniformStorage::name>(const int location, const name value) { _uniformEntries_##name##[location].Uniform.SetInstantly(value); } \
\
template <> \
inline void UniformStorage::SetSamplerUniformInstantly<UniformStorage::name>(const std::string& uniformName, const name value) { TRY_GET_LOCATION_NORET(SetSamplerUniformInstantly<name>(location, value);) } \


/**
 * \brief Create a template specialization for a ArrayUniform 
 * \param baseName Name of type to use in array (Float, Int etc...)
 */
#define ARRAY_UNIFORM_INIT(baseName) \
template <> \
inline void UniformStorage::InitializeArrayUniform<UniformStorage::##baseName##>(const std::string uniformName, std::vector<##baseName##> defaultValue, const bool includeInApplyQueue, const bool resetAfterApply) \
{ \
    const int location = AddUniform(uniformName); \
    InitializeArrayUniform<##baseName##, &UniformStorage::_uniformEntries_##baseName##V##>(uniformName, location, defaultValue, includeInApplyQueue, resetAfterApply); \
} \
\
template<> inline ArrayUniform<UniformStorage::baseName>* UniformStorage::GetArrayUniform(const int location) {  return &_uniformEntries_##baseName##V##[location].Uniform; } \
\
template<> inline ArrayUniform<UniformStorage::baseName>* UniformStorage::GetArrayUniform(const std::string& uniformName) { TRY_GET_LOCATION(return GetArrayUniform<baseName>(location)); }  \
\
template <> \
inline void UniformStorage::SetArrayUniform<UniformStorage::baseName>(const int location, const baseName value, size_t index) { _uniformEntries_##baseName##V##[location].Uniform.Set(value, index); } \
\
template <> \
inline void UniformStorage::SetArrayUniform<UniformStorage::baseName>(const std::string& uniformName, const baseName value, size_t index) { TRY_GET_LOCATION_NORET(SetArrayUniform<baseName>(location, value, index);) } \
\
template <> \
inline void UniformStorage::SetArrayUniformInstantly<UniformStorage::baseName>(const int location, const baseName value, size_t index) { _uniformEntries_##baseName##V##[location].Uniform.SetInstantly(value, index); } \
\
template <> \
inline void UniformStorage::SetArrayUniformInstantly<UniformStorage::baseName>(const std::string& uniformName, const baseName value, size_t index) { TRY_GET_LOCATION_NORET(SetArrayUniformInstantly<baseName>(location, value, index);) } \


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
                        T    Uniform;
                        bool ApplyInQueue;
                        bool ResetAfterApply;
                };

                UNIFORM(int, Int)
                UNIFORM(float, Float)
                UNIFORM(glm::vec4, Vec4)
                UNIFORM(glm::vec3, Vec3)
                UNIFORM(glm::vec2, Vec2)
                UNIFORM(glm::mat4, Mat4)

                ARRAY_UNIFORM(int, Int)
                ARRAY_UNIFORM(float, Float)
                ARRAY_UNIFORM(glm::vec4, Vec4)
                ARRAY_UNIFORM(glm::vec3, Vec3)
                ARRAY_UNIFORM(glm::vec2, Vec2)
                ARRAY_UNIFORM(glm::mat4, Mat4)

                SAMPLER_UNIFORM(Texture*, Texture)
                SAMPLER_UNIFORM(CubeMap*, CubeMap)

                GLuint                          _programID;
                std::map<std::string, int>      _uniformNameLocationMap;
                std::map<int, std::vector<int>> _applyQueue;
                bool                            _isTemplate              = false;
                int                             _invalidLocationsCounter = 0;

                int  AddUniform(const std::string& uniformName);
                void CheckUniformLocation(const std::string& uniformName, const int location) const;

                template <typename T>
                static void ShowUniformNotSupportedError() { Debug::Log::Error("Uniform type " + std::string(typeid(T).name()) + " is not supported"); }

                template <typename T, std::map<int, UniformEntry<Uniform<T>>> UniformStorage::*MapPtr>
                void InitializeUniform(
                    std::string uniformName,
                    int         location,
                    T           defaultVar,
                    const bool  includeInApplyQueue = true,
                    const bool  resetAfterApply     = false
                )
                {
                    (this->*MapPtr).emplace(location, UniformEntry<Uniform<T>>{Uniform<T>{_programID, uniformName, location, defaultVar}, includeInApplyQueue, resetAfterApply});

                    CheckUniformLocation(uniformName, location);
                }

                template <typename T, std::map<int, UniformEntry<ArrayUniform<T>>> UniformStorage::*MapPtr>
                void InitializeArrayUniform(
                    std::string uniformName,
                    int         location,
                    std::vector<T> defaultValue,
                    const bool  includeInApplyQueue = true,
                    const bool  resetAfterApply     = false
                )
                {
                    (this->*MapPtr).emplace(location, UniformEntry<ArrayUniform<T>>{ArrayUniform<T>{_programID, uniformName, location, defaultValue}, includeInApplyQueue, resetAfterApply});

                    CheckUniformLocation(uniformName, location);
                }

                template <typename T, std::map<int, UniformEntry<SamplerUniform<T>>> UniformStorage::*MapPtr>
                void InitializeSamplerUniform(
                    std::string uniformName,
                    int         location, T defaultValue,
                    const bool  includeInApplyQueue = true,
                    const bool  resetAfterApply     = false
                )
                {
                    (this->*MapPtr).emplace(location, UniformEntry<SamplerUniform<T>>{
                                                SamplerUniform<T>{_programID, uniformName, location, defaultValue}, includeInApplyQueue, resetAfterApply
                                            });

                    CheckUniformLocation(uniformName, location);
                }

            public:
                explicit UniformStorage();
                explicit UniformStorage(const GLuint programID);

                void Apply();

                int GetUniformLocation(const std::string& uniformName);

                UniformStorage* Copy(const GLuint programID) const;
                void            CopyTo(UniformStorage* uniformStorage) const;
                void            CopyFrom(const UniformStorage* uniformStorage);

                #pragma region Normal Uniforms
                template <typename T>
                void InitializeUniform(const std::string uniformName, T defaultValue, const bool includeInApplyQueue = true, const bool resetAfterApply = false)
                {
                    ShowUniformNotSupportedError<T>();
                }

                template <typename T>
                Uniform<T>* GetUniform(const std::string& uniformName)
                {
                    ShowUniformNotSupportedError<T>();
                    return nullptr;
                }

                template <typename T>
                Uniform<T>* GetUniform(const int location)
                {
                    ShowUniformNotSupportedError<T>();
                    return nullptr;
                }

                template <typename T>
                void SetUniform(const std::string& uniformName, T value) { ShowUniformNotSupportedError<T>(); }

                template <typename T>
                void SetUniform(int location, T value) { ShowUniformNotSupportedError<T>(); }

                template <typename T>
                void SetUniformInstantly(const std::string& uniformName, T value) { ShowUniformNotSupportedError<T>(); }

                template <typename T>
                void SetUniformInstantly(int location, T value) { ShowUniformNotSupportedError<T>(); }
                #pragma endregion

                #pragma region Array Uniforms
                template <typename T>
                void InitializeArrayUniform(const std::string uniformName, std::vector<T> defaultValue, const bool includeInApplyQueue = true, const bool resetAfterApply = false)
                {
                    ShowUniformNotSupportedError<std::vector<T>>();
                }

                template <typename T>
                ArrayUniform<T>* GetArrayUniform(const std::string& uniformName)
                {
                    ShowUniformNotSupportedError<T>();
                    return nullptr;
                }

                template <typename T>
                ArrayUniform<T>* GetArrayUniform(const int location)
                {
                    ShowUniformNotSupportedError<T>();
                    return nullptr;
                }

                template <typename T>
                void SetArrayUniform(const std::string& uniformName, T value, size_t index) { ShowUniformNotSupportedError<T>(); }

                template <typename T>
                void SetArrayUniform(int location, T value, size_t index) { ShowUniformNotSupportedError<T>(); }

                template <typename T>
                void SetArrayUniformInstantly(const std::string& uniformName, T value, size_t index) { ShowUniformNotSupportedError<T>(); }

                template <typename T>
                void SetArrayUniformInstantly(int location, T value, size_t index) { ShowUniformNotSupportedError<T>(); }
                #pragma endregion

                #pragma region Normal Uniforms
                template <typename T>
                void InitializeSamplerUniform(const std::string uniformName, T defaultValue, const bool includeInApplyQueue = true, const bool resetAfterApply = false)
                {
                    ShowUniformNotSupportedError<T>();
                }

                template <typename T>
                SamplerUniform<T>* GetSamplerUniform(const std::string& uniformName)
                {
                    ShowUniformNotSupportedError<T>();
                    return nullptr;
                }

                template <typename T>
                SamplerUniform<T>* GetSamplerUniform(const int location)
                {
                    ShowUniformNotSupportedError<T>();
                    return nullptr;
                }

                template <typename T>
                void SetSamplerUniform(const std::string& uniformName, T value) { ShowUniformNotSupportedError<T>(); }

                template <typename T>
                void SetSamplerUniform(int location, T value) { ShowUniformNotSupportedError<T>(); }

                template <typename T>
                void SetSamplerUniformInstantly(const std::string& uniformName, T value) { ShowUniformNotSupportedError<T>(); }

                template <typename T>
                void SetSamplerUniformInstantly(int location, T value) { ShowUniformNotSupportedError<T>(); }
                #pragma endregion
        };

        UNIFORM_INIT(Float)
        UNIFORM_INIT(Int)
        UNIFORM_INIT(Vec2)
        UNIFORM_INIT(Vec3)
        UNIFORM_INIT(Vec4)
        UNIFORM_INIT(Mat4)

        ARRAY_UNIFORM_INIT(Float)
        ARRAY_UNIFORM_INIT(Int)
        ARRAY_UNIFORM_INIT(Vec2)
        ARRAY_UNIFORM_INIT(Vec3)
        ARRAY_UNIFORM_INIT(Vec4)
        ARRAY_UNIFORM_INIT(Mat4)

        SAMPLER_UNIFORM_INIT(TextureSampler)
        SAMPLER_UNIFORM_INIT(CubeMapSampler)
    }
}
