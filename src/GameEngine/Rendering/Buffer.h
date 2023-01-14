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
                GLuint         _bufferID = 0;
                unsigned char* _buffer;
                unsigned int   _elementSize;
                unsigned int   _numElements;
                GLenum         _drawType;

            public:
                explicit Buffer(unsigned char* buffer, const unsigned int elementSize, const unsigned int numElements, const GLenum drawType = GL_STATIC_DRAW):
                    _buffer(buffer),
                    _elementSize(elementSize),
                    _numElements(numElements),
                    _drawType(drawType)
                {
                    glGenBuffers(1, &_bufferID);
                    Bind();
                    glBufferData(BufferType, numElements * elementSize, buffer, _drawType);
                    Unbind();
                }

                ~Buffer()
                {
                    glDeleteBuffers(1, &_bufferID);
                    delete[] _buffer;
                }

                unsigned int GetElementSize() const { return _elementSize; }
                unsigned int GetNumElements() const { return _numElements; }

                void Bind() const
                {
                    glBindBuffer(BufferType, _bufferID);
                }

                static void Unbind()
                {
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                }

                void UpdateData(const unsigned char* data, const unsigned int numElements)
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
