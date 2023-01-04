#include "UniformBuffer.h"

using namespace GameEngine::Rendering;


#define APPLY_UNIFORM(suffix) \
for (auto& uniform##suffix : _uniform##suffix##s) \
{ \
    if (uniform##suffix##.second.ApplyInQueue) { uniform##suffix##.second.Uniform.Apply(); } \
    if (uniform##suffix##.second.ResetAfterApply) { uniform##suffix##.second.Uniform.Reset(); } \
}


UniformBuffer::UniformBuffer(const GLuint programID):
    _programID(programID) {}

void UniformBuffer::Apply()
{
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


int UniformBuffer::GetUniformLocation(const GLchar* uniformName)
{
    if (_uniformNameLocationMap.find(uniformName) == _uniformNameLocationMap.end()) { return -1; }
    return _uniformNameLocationMap[uniformName];
}
