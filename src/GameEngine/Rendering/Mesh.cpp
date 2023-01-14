#include "Mesh.h"

using namespace GameEngine::Rendering;

Mesh::Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout) { AddPrimitive(vertexBuffer, indexBuffer, vertexBufferLayout); }

Mesh::~Mesh()
{
    for (const Primitive* primitive : _primitives) { delete primitive; }
    _primitives.clear();
}

const std::vector<Primitive*>& Mesh::GetPrimitives() { return _primitives; }

void Mesh::AddPrimitive(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout)
{
    _primitives.push_back(new Primitive(vertexBuffer, indexBuffer, vertexBufferLayout));
}
