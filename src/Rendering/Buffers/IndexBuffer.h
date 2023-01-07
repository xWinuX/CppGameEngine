#pragma once
#include <glad/glad.h>

namespace GameEngine
{
    namespace Rendering
    {
        // TODO: Probably combine Index and VertexBuffer into a base class since they are basically the same
        class IndexBuffer
        {
            private:
                GLuint         _indexBufferID = 0;
                unsigned char* _pIndices;
                unsigned int   _numIndices;
                GLenum         _indicesType;
                unsigned int   _indexSize;
                GLenum         _drawType;

            public:
                IndexBuffer(unsigned char* pIndices, GLenum indicesType, unsigned int numIndices, GLenum drawType = GL_STATIC_DRAW);
                ~IndexBuffer();
                unsigned int GetNumIndices() const;
                GLenum       GetIndicesType() const;
                unsigned int GetIndexSize() const;
                void         Bind() const;
                void         Unbind();

                void UpdateData(const unsigned char* data, unsigned int numIndices);
        };
    }
}
