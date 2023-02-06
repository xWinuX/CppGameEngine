#pragma once
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Primitive.h"
#include "reactphysics3d/collision/TriangleMesh.h"

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
                reactphysics3d::TriangleMesh*  GetColliderMesh() const;

                void AddPrimitive(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout);
                void SetColliderMesh(reactphysics3d::TriangleMesh* triangleMesh);

            private:
                std::vector<Primitive*>       _primitives;
                reactphysics3d::TriangleMesh* _colliderMesh;
        };
    }
}
