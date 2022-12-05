#include "MeshRendererComponent.h"

#include "../Rendering/Renderer.h"

MeshRendererComponent::MeshRendererComponent(Mesh& pMesh, Material* pMaterial) :
    _pMesh(pMesh),
    _pMaterial(pMaterial),
    _vertexArrayObject(&pMesh)
{
}

Mesh& MeshRendererComponent::GetMesh() const { return _pMesh; }

Material* MeshRendererComponent::GetMaterial() { return _pMaterial; }

VertexArrayObject* MeshRendererComponent::GetVertexArrayObject() { return &_vertexArrayObject; }

Transform* MeshRendererComponent::GetTransform() { return nullptr; }

void MeshRendererComponent::OnDraw() { Renderer::Submit(this); }
