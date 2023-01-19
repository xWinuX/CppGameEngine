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
                std::vector<VertexBuffer*>       _vertexBuffers;
                std::vector<VertexBufferLayout*> _vertexBufferLayouts;

                IndexBuffer* _indexBuffer        = nullptr;
                GLuint       _vertexArrayObjectID = 0;

            public:
                explicit VertexArrayObject();
                explicit VertexArrayObject(const Primitive* primitive);
                explicit VertexArrayObject(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout, bool finalize = true);
                ~VertexArrayObject();

                void AddVertexBuffer(VertexBuffer* vertexBuffer, VertexBufferLayout* vertexBufferLayout);
                void SetIndexBuffer(IndexBuffer* indexBuffer);
                void Finalize() const;
                void Bind() const;
                void Render() const;
                void Render(int numIndices, unsigned int offset) const;
                void RenderInstanced(int numIndices, int instanceCount) const;
                void Unbind() const;
        };
    }
}
