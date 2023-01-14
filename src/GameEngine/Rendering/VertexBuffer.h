﻿#pragma once
#include <glad/glad.h>

#include "Buffer.h"


namespace GameEngine
{
    namespace Rendering
    {
        class VertexBuffer : public Buffer<GL_ARRAY_BUFFER>
        {
            public:
                VertexBuffer(unsigned char* buffer, const unsigned elementSize, const unsigned numElements, const GLenum drawType = GL_STATIC_DRAW):
                    Buffer(buffer, elementSize, numElements, drawType) {}
        };
    }
}
