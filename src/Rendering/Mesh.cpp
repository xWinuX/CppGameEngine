#include "Mesh.h"

using namespace GameEngine::Rendering;

Mesh::Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout)
{
    AddPrimitive(vertexBuffer, indexBuffer, vertexBufferLayout);
}

Mesh::~Mesh()
{
    for (const Primitive subMesh : _subMeshes)
    {
        delete subMesh.IndexBuffer;
        delete subMesh.VertexBuffer;
        delete subMesh.VertexBufferLayout;
    }

    _subMeshes.clear();
}

const std::vector<Mesh::Primitive>& Mesh::GetSubMeshes()
{
    return _subMeshes;
}

void Mesh::AddPrimitive(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout)
{
    _subMeshes.push_back({vertexBuffer, indexBuffer, vertexBufferLayout});
}
