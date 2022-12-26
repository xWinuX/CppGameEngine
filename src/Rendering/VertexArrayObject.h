#pragma once

#include "Mesh.h"
#include "vector"

class VertexArrayObject
{
    private:
        const VertexBufferLayout* _pVertexBufferLayout = nullptr;
        IndexBuffer*              _pIndexBuffer        = nullptr;

        GLuint                     _vertexArrayObjectID = 0;
        std::vector<VertexBuffer*> _vertexBuffers;
    public:
        explicit VertexArrayObject(const Mesh* pMesh);
        explicit VertexArrayObject(const VertexBufferLayout* pVertexBufferLayout);
        ~VertexArrayObject();

        void          AddVertexBuffer(VertexBuffer* pVertexBuffer);
        void          SetIndexBuffer(IndexBuffer* pIndexBuffer);
        void          Finalize() const;
        void          Bind() const;
        void          Render() const;
        static void   Unbind();
};
