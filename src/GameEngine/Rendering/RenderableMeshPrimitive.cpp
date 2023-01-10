#include "RenderableMeshPrimitive.h"

using namespace GameEngine::Rendering;

RenderableMeshPrimitive::RenderableMeshPrimitive(const Mesh::Primitive primitive, Material* material):
    _primitive(primitive),
    _material(material),
    _vertexArrayObject(new VertexArrayObject(primitive)) {}

RenderableMeshPrimitive::~RenderableMeshPrimitive() { delete _vertexArrayObject; }

void RenderableMeshPrimitive::OnDraw()
{
    _vertexArrayObject->Bind();
    _vertexArrayObject->Render();
    _vertexArrayObject->Unbind();
}

Material* RenderableMeshPrimitive::GetMaterial() { return _material; }

void RenderableMeshPrimitive::SetMaterial(Material* material) { _material = material; }
