#pragma once
#include <vector>

#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexBufferLayout.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Mesh
        {
            public:
                struct Primitive
                {
                    VertexBuffer*       VertexBuffer;
                    IndexBuffer*        IndexBuffer;
                    VertexBufferLayout* VertexBufferLayout;
                };

                Mesh() = default;
                Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout);
                ~Mesh();

                const std::vector<Primitive>& GetSubMeshes();
                
                void AddPrimitive(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout);
            private:
                std::vector<Primitive> _subMeshes;
        };
    }
}
