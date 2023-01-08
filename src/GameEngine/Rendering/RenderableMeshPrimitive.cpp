#include "RenderableMeshPrimitive.h"

GameEngine::Rendering::RenderableMeshPrimitive::RenderableMeshPrimitive(const GameEngine::Rendering::Mesh::Primitive primitive, GameEngine::Rendering::Material* material):
    _primitive(primitive),
    _material(material),
    _vertexArrayObject(new VertexArrayObject(primitive)) {}

GameEngine::Rendering::RenderableMeshPrimitive::~RenderableMeshPrimitive() { delete _vertexArrayObject; }

void GameEngine::Rendering::RenderableMeshPrimitive::OnDraw()
{
    _vertexArrayObject->Bind();
    _vertexArrayObject->Render();
    _vertexArrayObject->Unbind();
}

GameEngine::Rendering::Material* GameEngine::Rendering::RenderableMeshPrimitive::GetMaterial() { return _material; }

void GameEngine::Rendering::RenderableMeshPrimitive::SetMaterial(Material* material) { _material = material; }
