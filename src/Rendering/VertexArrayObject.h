#pragma once

#include "Mesh.h"
#include "vector"

namespace GameEngine
{
    namespace Rendering
    {
        class VertexArrayObject
        {
            private:
                const VertexBufferLayout* _pVertexBufferLayout = nullptr;
                IndexBuffer*              _pIndexBuffer        = nullptr;

                GLuint                     _vertexArrayObjectID = 0;
                std::vector<VertexBuffer*> _vertexBuffers;

            public:
                explicit VertexArrayObject(const Mesh* pMesh);
                explicit VertexArrayObject(VertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer, const VertexBufferLayout* pVertexBufferLayout);
                explicit VertexArrayObject(const VertexBufferLayout* pVertexBufferLayout);
                ~VertexArrayObject();

                void AddVertexBuffer(VertexBuffer* pVertexBuffer);
                void SetIndexBuffer(IndexBuffer* pIndexBuffer);
                void Finalize() const;
                void Bind() const;
                void Render() const;
                void Unbind() const;
        };
    }
}
