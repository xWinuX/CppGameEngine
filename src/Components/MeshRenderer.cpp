#include "MeshRenderer.h"

#include <iostream>

#include "../Rendering/Renderer.h"

MeshRenderer::MeshRenderer(Mesh* pMesh, Material* pMaterial) :
    _pMesh(pMesh),
    _pMaterial(pMaterial),
    _vertexArrayObject(pMesh)
{
    _vertexArrayObject.Finalize();
}

Mesh* MeshRenderer::GetMesh() const { return _pMesh; }

Material* MeshRenderer::GetMaterial() { return _pMaterial; }

VertexArrayObject* MeshRenderer::GetVertexArrayObject() { return &_vertexArrayObject; }

void MeshRenderer::OnStart()
{
    std::cout << "Start" << std::endl;
    Renderer::Submit(this);
}
