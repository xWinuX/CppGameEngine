#include "UniformBuffer.h"

void UniformBuffer::Bind(const unsigned int bindingPoint) const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, _bufferID);
}
