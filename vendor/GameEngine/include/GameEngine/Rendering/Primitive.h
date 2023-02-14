#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace GameEngine
{
    namespace Rendering
    {
        class VertexArrayObject;

        // TODO: evaluate if this is even needed, i could just put all this info in the vao class
        class Primitive
        {
            public:
                Primitive(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout);
                ~Primitive();
                VertexArrayObject*  GetVertexArrayObject() const;
                VertexBuffer*       GetVertexBuffer() const;
                IndexBuffer*        GetIndexBuffer() const;
                VertexBufferLayout* GetVertexBufferLayout() const;

            private:
                VertexBuffer*       _vertexBuffer;
                IndexBuffer*        _indexBuffer;
                VertexBufferLayout* _vertexBufferLayout;
                VertexArrayObject*  _vertexArrayObject;
        };
    }
}
