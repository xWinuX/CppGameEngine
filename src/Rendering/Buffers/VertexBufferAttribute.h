#pragma once
#include <glad/glad.h>

class VertexBufferAttribute
{
    private:
        GLint       _size;
        GLenum      _type;
        GLboolean   _normalized;
        GLsizei     _stride;
        const void* _pointer;

    public:
        VertexBufferAttribute():
            _size(0), _type(-1), _normalized(false), _stride(0), _pointer(nullptr) {}
        VertexBufferAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
        void  Bind(GLuint index) const;
        GLint GetSize() { return _size; }
};
