#pragma once
#include <glad/glad.h>

namespace GameEngine
{
    namespace Rendering
    {
        class VertexBufferAttribute
        {
            private:
                GLint        _size       = 0;
                GLenum       _type       = GL_NONE;
                GLboolean    _normalized = false;
                GLsizei      _stride     = 0;
                const void*  _offset     = nullptr;
                unsigned int _divisor    = 0;

            public:
                VertexBufferAttribute() = default;
                VertexBufferAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset, const unsigned int divisor = 0);
                void        Bind(GLuint index) const;
                static void Unbind(GLuint index);
                GLint       GetSize() const;
        };
    }
}
