#pragma once
#include "glad/glad.h"
#include "../Debug/Log.h"

namespace GameEngine
{
    namespace Rendering
    {
        template <GLenum BufferType>
        class Buffer
        {
            protected:
                GLuint _bufferID = 0;
                size_t _elementSize;
                size_t _numElements;
                GLenum _drawType;

            public:
                explicit Buffer(const unsigned char* buffer, const size_t elementSize, const size_t numElements, const GLenum drawType = GL_STATIC_DRAW):
                    _elementSize(elementSize),
                    _numElements(numElements),
                    _drawType(drawType)
                {
                    glGenBuffers(1, &_bufferID);
                    glBindBuffer(BufferType, _bufferID);
                    glBufferData(BufferType, static_cast<GLsizeiptr>(numElements * elementSize), buffer, _drawType);
                    glBindBuffer(BufferType, 0);
                }

                ~Buffer()
                {
                    glDeleteBuffers(1, &_bufferID);
                }

                size_t GetElementSize() const { return _elementSize; }
                size_t GetNumElements() const { return _numElements; }

                void Bind() const
                {
                    glBindBuffer(BufferType, _bufferID);
                }

                static void Unbind()
                {
                    glBindBuffer(BufferType, 0);
                }

                void UpdateData(const unsigned char* data, const size_t numElements)
                {
                    _numElements = numElements;

                    glBindBuffer(BufferType, _bufferID);
                    glBufferSubData(BufferType, 0, _numElements * _elementSize, data);
                    glBindBuffer(BufferType, 0);
                }

                void UpdateDataRange(const unsigned char* data, const size_t startOffset, const size_t numBytes) const
                {
                    glBindBuffer(BufferType, _bufferID);
                    glBufferSubData(BufferType, startOffset, startOffset+numBytes, data);
                    glBindBuffer(BufferType, 0);
                }
        };
    }
}
