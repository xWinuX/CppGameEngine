#pragma once

#include "vector"
#include "Primitive.h"

namespace GameEngine
{
    namespace Rendering
    {
        class VertexArrayObject
        {
            private:
                VertexBufferLayout* _pVertexBufferLayout = nullptr;
                IndexBuffer*        _pIndexBuffer        = nullptr;

                GLuint                     _vertexArrayObjectID = 0;
                std::vector<VertexBuffer*> _vertexBuffers;

            public:
                explicit VertexArrayObject(const Primitive* primitive);
                explicit VertexArrayObject(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout);
                explicit VertexArrayObject(VertexBufferLayout* pVertexBufferLayout);
                ~VertexArrayObject();

                void AddVertexBuffer(VertexBuffer* pVertexBuffer);
                void SetIndexBuffer(IndexBuffer* pIndexBuffer);
                void Finalize() const;
                void Bind() const;
                void Render() const;
                void Render(int numIndices, unsigned int offset) const;
                void Unbind() const;
        };
    }
}
