﻿#include "GameEngine/Rendering/UniformBuffer.h"

using namespace GameEngine::Rendering;

#define APPLY_UNIFORM(suffix) \
for (auto& uniform##suffix : _uniform##suffix##s) \
{ \
    if (uniform##suffix##.second.ApplyInQueue) { uniform##suffix##.second.Uniform.Apply(); } \
    if (uniform##suffix##.second.ResetAfterApply) { uniform##suffix##.second.Uniform.Reset(); } \
}

#define COPY_UNIFORM(type,suffix) \
for (auto uniform##suffix : _uniform##suffix##s) \
{ \
    uniformBuffer->InitializeUniform<##type##>(uniform##suffix##.second.Uniform.GetName(), uniform##suffix##.second.Uniform.GetDefaultValue(), uniform##suffix##.second.ApplyInQueue, uniform##suffix##.second.ResetAfterApply); \
}

UniformBuffer::UniformBuffer():
    _isTemplate(true) {}

UniformBuffer::UniformBuffer(const GLuint programID):
    _programID(programID) {}

void UniformBuffer::Apply()
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
    for (auto& uniformTexture : _uniformTextures)
    {
        uniformTexture.second.Uniform.Apply(slot);
        slot++;
    }
}


int UniformBuffer::GetUniformLocation(const std::string& uniformName)
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

UniformBuffer* UniformBuffer::Copy(const GLuint programID) const
{
    UniformBuffer* uniformBuffer = new UniformBuffer(programID);

    CopyTo(uniformBuffer);

    return uniformBuffer;
}

void UniformBuffer::CopyTo(UniformBuffer* uniformBuffer) const
{
    COPY_UNIFORM(glm::mat4, Mat4F)
    COPY_UNIFORM(glm::vec4, 4F)
    COPY_UNIFORM(std::vector<glm::vec4>*, 4FV)
    COPY_UNIFORM(glm::vec3, 3F)
    COPY_UNIFORM(std::vector<glm::vec3>*, 3FV)
    COPY_UNIFORM(int, 1I)
    COPY_UNIFORM(float, 1F)
    COPY_UNIFORM(std::vector<float>*, 1FV)
    COPY_UNIFORM(Texture*, Texture)
}

void UniformBuffer::CopyFrom(const UniformBuffer* uniformBuffer)
{
    uniformBuffer->CopyTo(this);
}