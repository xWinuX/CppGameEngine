#include "MeshRenderer.h"

#include <iostream>

#include "../Rendering/Renderer.h"

MeshRenderer::MeshRenderer(Mesh* pMesh, Material* pMaterial) :
    _pMesh(pMesh),
    _pMaterial(pMaterial),
    _vertexArrayObject(pMesh) { _vertexArrayObject.Finalize(); }

Mesh* MeshRenderer::GetMesh() const { return _pMesh; }

Material* MeshRenderer::GetMaterial() { return _pMaterial; }

void MeshRenderer::OnBeforeRender()
{
    if (!_visible) { return; }

    Renderer::SubmitRenderable(this);
}

void MeshRenderer::OnBeforeDraw() { _pMaterial->GetUniformBuffer()->SetUniformInstant("u_Transform", _transform->GetTRS()); }

void MeshRenderer::OnDraw()
{
    _vertexArrayObject.Bind();
    _vertexArrayObject.Render();
}

void MeshRenderer::OnStart()
{
    std::cout << "Start" << std::endl;
    Renderer::SubmitRenderable(this);
}
