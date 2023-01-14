#pragma once
#include <glad/glad.h>

namespace GameEngine
{
    namespace Rendering
    {
        class VertexBufferAttribute
        {
            private:
                GLint       _size;
                GLenum      _type;
                GLboolean   _normalized;
                GLsizei     _stride;
                const void* _offset;

            public:
                VertexBufferAttribute(): _size(0), _type(-1), _normalized(false), _stride(0), _offset(nullptr) {}

                VertexBufferAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);
                void        Bind(GLuint index) const;
                static void Unbind(GLuint index);
                GLint       GetSize() const { return _size; }
        };
    }
}
