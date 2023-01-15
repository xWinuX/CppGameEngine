#include "VertexBufferAttribute.h"

#include "../Debug/Log.h"

using namespace GameEngine::Rendering;

VertexBufferAttribute::VertexBufferAttribute(const GLint size, const GLenum type, const GLboolean normalized, const GLsizei stride, const void* offset)
{
    _size       = size;
    _type       = type;
    _normalized = normalized;
    _stride     = stride;
    _offset    = offset;
}

void VertexBufferAttribute::Bind(const GLuint index) const
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, _size, _type, _normalized, _stride, _offset);
}

void VertexBufferAttribute::Unbind(const GLuint index)
{
    glDisableVertexAttribArray(index);
}
