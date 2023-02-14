#include "GameEngine/Rendering/Mesh.h"

using namespace GameEngine::Rendering;

Mesh::Mesh(const std::string& name, const glm::vec3 translation):
    _name(name),
    _translation(translation) {}

Mesh::Mesh(const std::string& name, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout, glm::vec3 translation):
    Mesh(name, translation) { AddPrimitive(vertexBuffer, indexBuffer, vertexBufferLayout); }

Mesh::~Mesh()
{
    for (const Primitive* primitive : _primitives) { delete primitive; }
    _primitives.clear();
}

const std::vector<Primitive*>& Mesh::GetPrimitives() { return _primitives; }
reactphysics3d::TriangleMesh*  Mesh::GetColliderMesh() const { return _colliderMesh; }
const std::string&             Mesh::GetName() { return _name; }
glm::vec3                      Mesh::GetTranslation() const { return _translation; }

void Mesh::AddPrimitive(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, VertexBufferLayout* vertexBufferLayout)
{
    Debug::Log::Message(std::to_string(vertexBuffer->GetNumElements()));
    Debug::Log::Message(std::to_string(indexBuffer->GetNumElements()));
    _primitives.push_back(new Primitive(vertexBuffer, indexBuffer, vertexBufferLayout));
}

void Mesh::SetColliderMesh(reactphysics3d::TriangleMesh* triangleMesh) { _colliderMesh = triangleMesh; }
