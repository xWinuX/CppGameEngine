#pragma once
#include <glad/glad.h>

class VertexAttribute
{
    private:
        GLint       _size;
        GLenum      _type;
        GLboolean   _normalized;
        GLsizei     _stride;
        const void* _pointer;
    public:
        VertexAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
         void Bind(GLuint index) const;
};
