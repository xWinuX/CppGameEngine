#include "GameEngine/Rendering/Mesh.h"

using namespace GameEngine::Rendering;

Mesh::Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout) { AddPrimitive(vertexBuffer, indexBuffer, vertexBufferLayout); }

Mesh::~Mesh()
{
    for (const Primitive* primitive : _primitives) { delete primitive; }
    _primitives.clear();
}

const std::vector<Primitive*>& Mesh::GetPrimitives() { return _primitives; }
reactphysics3d::TriangleMesh*  Mesh::GetColliderMesh() const { return _colliderMesh; }

void Mesh::AddPrimitive(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout)
{
    Debug::Log::Message(std::to_string(vertexBuffer->GetNumElements()));
    Debug::Log::Message(std::to_string(indexBuffer->GetNumElements()));
    _primitives.push_back(new Primitive(vertexBuffer, indexBuffer, vertexBufferLayout));
}

void Mesh::SetColliderMesh(reactphysics3d::TriangleMesh* triangleMesh) { _colliderMesh = triangleMesh; }
