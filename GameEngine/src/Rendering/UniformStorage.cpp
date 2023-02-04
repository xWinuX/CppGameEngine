#include "GameEngine/Rendering/UniformStorage.h"

#include "GameEngine/Rendering/CubeMap.h"

using namespace GameEngine::Rendering;

#define APPLY_UNIFORM(type) \
for (auto& uniform : _uniformEntries_##type##) \
{ \
    if (uniform.second.ApplyInQueue) { uniform.second.Uniform.Apply(); } \
    if (uniform.second.ResetAfterApply) { uniform.second.Uniform.Reset(); } \
}

#define APPLY_SAMPLER_UNIFORM(type) \
for (auto& uniform : _uniformEntries_##type##) \
{ \
    uniform.second.Uniform.Apply(slot); \
    slot++; \
    if (uniform.second.ResetAfterApply) { uniform.second.Uniform.Reset(); } \
}

#define COPY_UNIFORM(type) \
for (auto uniform : _uniformEntries_##type##) \
{ \
    uniformStorage->InitializeUniform<##type##>(uniform.second.Uniform.GetName(), uniform.second.Uniform.GetDefaultValue(), uniform.second.ApplyInQueue, uniform.second.ResetAfterApply); \
}

#define COPY_ARRAY_UNIFORM(type) \
for (auto uniform : _uniformEntries_##type##V##) \
{ \
    uniformStorage->InitializeArrayUniform<##type##>(uniform.second.Uniform.GetName(), uniform.second.Uniform.GetDefaultValue(), uniform.second.ApplyInQueue, uniform.second.ResetAfterApply); \
}

#define COPY_SAMPLER_UNIFORM(type) \
for (auto uniform : _uniformEntries_##type##) \
{ \
    uniformStorage->InitializeSamplerUniform<##type##>(uniform.second.Uniform.GetName(), uniform.second.Uniform.GetDefaultValue(), uniform.second.ApplyInQueue, uniform.second.ResetAfterApply); \
}

int UniformStorage::AddUniform(const std::string& uniformName) {
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

    return location;
}

void UniformStorage::CheckUniformLocation(const std::string& uniformName, const int location) const {
    if (location < 0 && !_isTemplate) { Debug::Log::Error("Something went wrong initializing uniform " + uniformName); }
}

UniformStorage::UniformStorage():
    _isTemplate(true) {}

UniformStorage::UniformStorage(const GLuint programID):
    _programID(programID) {}

void UniformStorage::Apply()
{
    if (_isTemplate)
    {
        Debug::Log::Error("Can't apply template uniform buffer!");
        return;
    }

    APPLY_UNIFORM(Int)
    APPLY_UNIFORM(Float)
    APPLY_UNIFORM(Vec3)
    APPLY_UNIFORM(Vec4)
    APPLY_UNIFORM(Mat4)

    APPLY_UNIFORM(IntV)
    APPLY_UNIFORM(FloatV)
    APPLY_UNIFORM(Vec3V)
    APPLY_UNIFORM(Vec4V)
    APPLY_UNIFORM(Mat4V)

    int slot = 0;
    APPLY_SAMPLER_UNIFORM(TextureSampler)
    APPLY_SAMPLER_UNIFORM(CubeMapSampler)
}


int UniformStorage::GetUniformLocation(const std::string& uniformName)
{
    if (_isTemplate)
    {
        Debug::Log::Error("Can't get location of template uniform buffer");
        return -1;
    }

    if (_uniformNameLocationMap.find(uniformName) == _uniformNameLocationMap.end())
    {
        Debug::Log::Message(std::string(uniformName) + "not found");
        return -1;
    }

    return _uniformNameLocationMap[uniformName];
}

UniformStorage* UniformStorage::Copy(const GLuint programID) const
{
    UniformStorage* uniformStorage = new UniformStorage(programID);

    CopyTo(uniformStorage);

    return uniformStorage;
}

void UniformStorage::CopyTo(UniformStorage* uniformStorage) const
{
    COPY_UNIFORM(Int)
    COPY_UNIFORM(Float)
    COPY_UNIFORM(Vec3)
    COPY_UNIFORM(Vec4)
    COPY_UNIFORM(Mat4)

    COPY_ARRAY_UNIFORM(Int)
    COPY_ARRAY_UNIFORM(Float)
    COPY_ARRAY_UNIFORM(Vec3)
    COPY_ARRAY_UNIFORM(Vec4)
    COPY_ARRAY_UNIFORM(Mat4)

    COPY_SAMPLER_UNIFORM(TextureSampler)
    COPY_SAMPLER_UNIFORM(CubeMapSampler)
}

void UniformStorage::CopyFrom(const UniformStorage* uniformStorage) { uniformStorage->CopyTo(this); }
