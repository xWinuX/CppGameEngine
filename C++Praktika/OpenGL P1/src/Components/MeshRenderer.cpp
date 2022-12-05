#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Mesh* pMesh, Material* pMaterial) : _vertexArrayObject(pMesh->PVertexBufferLayout)
{
    _pMesh     = pMesh;
    _pMaterial = pMaterial;

    _vertexArrayObject.AddVertexBuffer(_pMesh->PVertexBuffer);
    _vertexArrayObject.SetIndexBuffer(_pMesh->PIndexBuffer);
}

Mesh* MeshRenderer::GetMesh() const { return _pMesh; }

Material* MeshRenderer::GetMaterial() { return _pMaterial; }

VertexArrayObject* MeshRenderer::GetVertexArrayObject() { return &_vertexArrayObject; }

Transform* MeshRenderer::GetTransform()
{
    return nullptr;
}
