#include "GameEngine/Rendering/UniformStorage.h"

#include "GameEngine/Rendering/CubeMap.h"

using namespace GameEngine::Rendering;

#define APPLY_UNIFORM(suffix) \
for (auto& uniform##suffix : _uniform##suffix##s) \
{ \
    if (uniform##suffix##.second.ApplyInQueue) { uniform##suffix##.second.Uniform.Apply(); } \
    if (uniform##suffix##.second.ResetAfterApply) { uniform##suffix##.second.Uniform.Reset(); } \
}

#define DRAW_UNIFORM(suffix) \
for (auto& uniform##suffix : _uniform##suffix##s) \
{ \
    if (uniform##suffix##.second.ApplyInQueue) { uniform##suffix##.second.Uniform.Draw(fieldIdentifier); } \
}

#define APPLY_SAMPLER_UNIFORM(suffix) \
for (auto& uniform##suffix : _uniform##suffix##s) \
{ \
    if (uniform##suffix##.second.ApplyInQueue) \
    { \
        uniform##suffix##.second.Uniform.Apply(slot); \
        slot++; \
    } \
    if (uniform##suffix##.second.ResetAfterApply) { uniform##suffix##.second.Uniform.Reset(); } \
}
#define COPY_UNIFORM(type,suffix) \
for (auto uniform##suffix : _uniform##suffix##s) \
{ \
    uniformStorage->InitializeUniform<##type##>(uniform##suffix##.second.Uniform.GetName(), uniform##suffix##.second.Uniform.GetDefaultValue(), uniform##suffix##.second.ApplyInQueue, uniform##suffix##.second.ResetAfterApply); \
}

UniformStorage::UniformStorage():
    _isTemplate(true) {}

UniformStorage::UniformStorage(const GLuint programID):
    _programID(programID) {}

void UniformStorage::DrawProperties(const std::string& fieldIdentifier)
{
    DRAW_UNIFORM(1I)
    DRAW_UNIFORM(4F)
    DRAW_UNIFORM(4FV)
    DRAW_UNIFORM(3F)
    DRAW_UNIFORM(3FV)
    DRAW_UNIFORM(1F)
    DRAW_UNIFORM(1FV)
    DRAW_UNIFORM(Mat4F)
    DRAW_UNIFORM(Texture2D)
}

void UniformStorage::Apply()
{
    if (_isTemplate)
    {
        Debug::Log::Error("Can't apply template uniform buffer!");
        return;
    }

    APPLY_UNIFORM(1I)
    APPLY_UNIFORM(4F)
    APPLY_UNIFORM(4FV)
    APPLY_UNIFORM(3F)
    APPLY_UNIFORM(3FV)
    APPLY_UNIFORM(1F)
    APPLY_UNIFORM(1FV)
    APPLY_UNIFORM(Mat4F)

    int slot = 0;
    APPLY_SAMPLER_UNIFORM(Texture2D)
    APPLY_SAMPLER_UNIFORM(Texture2DArray)
    APPLY_SAMPLER_UNIFORM(CubeMap)
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
    COPY_UNIFORM(glm::mat4, Mat4F)
    COPY_UNIFORM(glm::vec4, 4F)
    COPY_UNIFORM(std::vector<glm::vec4>*, 4FV)
    COPY_UNIFORM(glm::vec3, 3F)
    COPY_UNIFORM(std::vector<glm::vec3>*, 3FV)
    COPY_UNIFORM(int, 1I)
    COPY_UNIFORM(float, 1F)
    COPY_UNIFORM(std::vector<float>*, 1FV)
    COPY_UNIFORM(Texture2D*, Texture2D)
    COPY_UNIFORM(Texture2DArray*, Texture2DArray)
    COPY_UNIFORM(CubeMap*, CubeMap)
}

void UniformStorage::CopyFrom(const UniformStorage* uniformStorage) { uniformStorage->CopyTo(this); }
