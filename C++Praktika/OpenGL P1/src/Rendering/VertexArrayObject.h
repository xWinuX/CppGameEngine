#pragma once

#include "Mesh.h"
#include "vector"

class VertexArrayObject
{
    private:
        const VertexBufferLayout* _pVertexBufferLayout;

        GLuint                     _vertexArrayObjectID;
        IndexBuffer*               _pIndexBuffer;
        std::vector<VertexBuffer*> _vertexBuffers;
    public:
        ~VertexArrayObject();
        VertexArrayObject(const VertexBufferLayout* pVertexBufferLayout);

        void        AddVertexBuffer(VertexBuffer* pVertexBuffer);
        void        SetIndexBuffer(IndexBuffer* pIndexBuffer);
        void        Bind() const;
        static void Unbind();
};
