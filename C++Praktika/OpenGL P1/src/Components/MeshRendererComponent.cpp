#include "MeshRendererComponent.h"

MeshRendererComponent::MeshRendererComponent(Mesh* pMesh, Material* pMaterial) : _vertexArrayObject(pMesh->PVertexBufferLayout)
{
    _pMesh     = pMesh;
    _pMaterial = pMaterial;

    _vertexArrayObject.AddVertexBuffer(_pMesh->PVertexBuffer);
    _vertexArrayObject.SetIndexBuffer(_pMesh->PIndexBuffer);
}

Mesh* MeshRendererComponent::GetMesh() const { return _pMesh; }

Material* MeshRendererComponent::GetMaterial() { return _pMaterial; }

VertexArrayObject* MeshRendererComponent::GetVertexArrayObject() { return &_vertexArrayObject; }
