#include "UniformBuffer.h"

#define APPLY_UNIFORM(suffix) \
for (auto& uniform##suffix : _uniform##suffix##s) \
{ \
    if (!uniform##suffix##.second.ApplyInQueue) { continue; } \
    uniform##suffix##.second.Uniform.Apply(); \
}

UniformBuffer::UniformBuffer(const GLuint programID):
    _programID(programID) {}

void UniformBuffer::Apply() 
{
    APPLY_UNIFORM(1I)
    APPLY_UNIFORM(4F)
    APPLY_UNIFORM(Mat4F)
}

int UniformBuffer::GetUniformLocation(const GLchar* uniformName)
{
    if (_uniformNameLocationMap.find(uniformName) == _uniformNameLocationMap.end()) { return -1; }
    return _uniformNameLocationMap[uniformName];
}
