#pragma once
#include <glad/glad.h>


namespace GameEngine
{
    namespace Rendering
    {
        class VertexBuffer
        {
            private:
            GLuint         _vertexBufferID = 0;
            unsigned char* _pVertices;
            unsigned int   _stride;
            unsigned int   _numVertices;
            public:
            explicit VertexBuffer(unsigned char* pVertices, unsigned int stride, unsigned int numVertices);
            ~VertexBuffer();
            void        Bind() const;
            static void Unbind();

            unsigned char* PVertices() const { return _pVertices; }
            unsigned       NumVertices() const { return _numVertices; }
        };
    }
}