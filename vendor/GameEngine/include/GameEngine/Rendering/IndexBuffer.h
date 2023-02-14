#pragma once
#include <glad/glad.h>

#include "Buffer.h"

namespace GameEngine
{
    namespace Rendering
    {
        class IndexBuffer : public Buffer<GL_ELEMENT_ARRAY_BUFFER>
        {
            public:
                IndexBuffer(unsigned char* buffer, const size_t elementSize, const size_t numElements, const GLenum drawType = GL_STATIC_DRAW):
                    Buffer(buffer, elementSize, numElements, drawType)
                {
                    switch (_elementSize)
                    {
                        case sizeof(GLuint): _indicesType = GL_UNSIGNED_INT;
                            break;
                        case sizeof(GLushort): _indicesType = GL_UNSIGNED_SHORT;
                            break;
                        case sizeof(GLubyte): _indicesType = GL_UNSIGNED_BYTE;
                            break;
                        default: Debug::Log::Error("Given index buffer element size doesn't match any of the sizes of (GLuint, GLushort, GLubyte)");
                            break;
                    }
                }

                GLenum GetIndicesType() const { return _indicesType; }

            private:
                GLenum _indicesType;
        };
    }
}
