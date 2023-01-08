#pragma once
#include <glad/glad.h>


namespace GameEngine
{
    namespace Rendering
    {
        // TODO: Probably combine Index and VertexBuffer into a base class since they are basically the same
        class VertexBuffer
        {
            private:
                GLuint         _vertexBufferID = 0;
                unsigned char* _pVertices;
                unsigned int   _vertexSize;
                unsigned int   _numVertices;
                GLenum         _drawType;

            public:
                explicit VertexBuffer(unsigned char* pVertices, unsigned int vertexSize, unsigned int numVertices, GLenum drawType = GL_STATIC_DRAW);
                ~VertexBuffer();
                void Bind() const;
                void Unbind();

                void UpdateData(const unsigned char* data, const unsigned int numVertices);

                unsigned char* PVertices() const { return _pVertices; }
                unsigned       NumVertices() const { return _numVertices; }
        };
    }
}
