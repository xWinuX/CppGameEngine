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
                unsigned char* _buffer;
                GLuint         _bufferID = 0;
                size_t         _elementSize;
                size_t         _numElements;
                GLenum         _drawType;

            public:
                explicit Buffer(unsigned char* buffer, const size_t elementSize, const size_t numElements, const GLenum drawType = GL_STATIC_DRAW):
                    _buffer(buffer),
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
                    
                    delete[] _buffer;
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

                /**
                 * \brief Updates data of the buffer with given data. The data will be updated from the start of the buffer
                 * \param data New data
                 * \param numElements Number of elements to update
                 * \param updateInternalBuffer Should the internal buffer be updated? (Default value is false, setting it to true will cost performance because data will be copied)
                 */
                void UpdateData(const unsigned char* data, const size_t numElements, const bool updateInternalBuffer = false) const
                {
                    UpdateDataRange(data, 0, numElements * _elementSize, updateInternalBuffer);
                }

                /**
                 * \brief 
                 * \param data New data
                 * \param startOffsetInBytes Offset in bytes where to start inserting data into the buffer
                 * \param numBytes Number of bytes to insert
                 * \param updateInternalBuffer Should the internal buffer be updated? (Default value is false, setting it to true will cost performance because data will be copied)
                 */
                void UpdateDataRange(const unsigned char* data, const size_t startOffsetInBytes, const size_t numBytes, const bool updateInternalBuffer = false) const
                {
                    if (updateInternalBuffer) { memcpy(_buffer, data, numBytes); }

                    glBindBuffer(BufferType, _bufferID);
                    glBufferSubData(BufferType, startOffsetInBytes, startOffsetInBytes + numBytes, data);
                }
        };
    }
}
