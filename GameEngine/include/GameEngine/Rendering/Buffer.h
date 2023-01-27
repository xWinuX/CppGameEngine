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
                    Bind();
                    glBufferData(BufferType, static_cast<GLsizeiptr>(numElements * elementSize), buffer, _drawType);
                    Unbind();
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
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                }

                void UpdateData(const unsigned char* data, const size_t numElements)
                {
                    if (_drawType != GL_DYNAMIC_DRAW)
                    {
                        Debug::Log::Error("You can't update data on a static vertex buffer!");
                        return;
                    }

                    _numElements = numElements;

                    Bind();
                    glBufferSubData(BufferType, 0, _numElements * _elementSize, data);
                }
        };
    }
}
