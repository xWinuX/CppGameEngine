#pragma once
#include "Buffer.h"

class UniformBuffer : public GameEngine::Rendering::Buffer<GL_UNIFORM_BUFFER>
{
    public:
        UniformBuffer(unsigned char* buffer, const size_t elementSize, const size_t numElements, const GLenum drawType):
            Buffer(buffer, elementSize, numElements, drawType) {}

        void Bind(const unsigned int bindingPoint) const;
};
