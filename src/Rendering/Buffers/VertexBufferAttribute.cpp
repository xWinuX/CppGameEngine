#include "VertexBufferAttribute.h"

using namespace GameEngine::Rendering;

VertexBufferAttribute::VertexBufferAttribute(const GLint size, const GLenum type, const GLboolean normalized, const GLsizei stride, const void* pointer)
{
    _size       = size;
    _type       = type;
    _normalized = normalized;
    _stride     = stride;
    _pointer    = pointer;
}

void VertexBufferAttribute::Bind(const GLuint index) const
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, _size, _type, _normalized, _stride, _pointer);
}

void VertexBufferAttribute::Unbind(const GLuint index)
{
    glDisableVertexAttribArray(index);
}
