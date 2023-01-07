#include "MeshRenderer.h"

#include "../Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;

MeshRenderer::MeshRenderer(Mesh* pMesh, Material* pMaterial) :
    _pMesh(pMesh),
    _pMaterial(pMaterial),
    _pVertexArrayObject(new VertexArrayObject(pMesh)) { _pVertexArrayObject->Finalize(); }

MeshRenderer::~MeshRenderer()
{
    delete _pVertexArrayObject;
}

Mesh* MeshRenderer::GetMesh() const { return _pMesh; }

Material* MeshRenderer::GetMaterial() { return _pMaterial; }

void MeshRenderer::OnBeforeRender()
{
    if (!_visible) { return; }

    Renderer::SubmitRenderable(this);
}

void MeshRenderer::OnBeforeDraw()
{
    const glm::mat4 trs = _transform->GetTRS();
    _pMaterial->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_Transform", trs);
}

void MeshRenderer::OnDraw()
{
    _pVertexArrayObject->Bind();
    _pVertexArrayObject->Render();
    _pVertexArrayObject->Unbind();
}

void MeshRenderer::OnStart()
{
    Renderer::SubmitRenderable(this);
}
