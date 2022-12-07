#pragma once
#include <glad/glad.h>

#include "../Vertex.h"

class VertexBuffer
{
    private:
        GLuint       _vertexBufferID = 0;
        VertexPos*   _pVertices;
        unsigned int _numVertices;
    public:
        explicit VertexBuffer(VertexPos* pVertices, unsigned int numVertices);
        ~VertexBuffer();
        void     Bind() const;
        static void Unbind();

        VertexPos* PVertices() const { return _pVertices; }
        unsigned   NumVertices() const { return _numVertices; }
};
