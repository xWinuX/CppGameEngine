#include "GameEngine/Rendering/VertexBufferAttribute.h"

using namespace GameEngine::Rendering;

VertexBufferAttribute::VertexBufferAttribute(const GLint size, const GLenum type, const GLboolean normalized, const GLsizei stride, const void* offset, const unsigned int divisor):
    _size(size),
    _type(type),
    _normalized(normalized),
    _stride(stride),
    _offset(offset),
    _divisor(divisor) {}

void VertexBufferAttribute::Bind(const GLuint index) const
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, _size, _type, _normalized, _stride, _offset);
    glVertexAttribDivisor(index, _divisor);
}

void VertexBufferAttribute::Unbind(const GLuint index)
{
    glDisableVertexAttribArray(index);
}

GLint VertexBufferAttribute::GetSize() const { return _size; }
