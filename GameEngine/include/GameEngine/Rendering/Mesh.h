#pragma once
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Primitive.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Mesh
        {
            public:
                Mesh() = default;
                Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout);
                ~Mesh();

                const std::vector<Primitive*>& GetPrimitives();

                void AddPrimitive(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout);

            private:
                std::vector<Primitive*> _primitives;
        };
    }
}
