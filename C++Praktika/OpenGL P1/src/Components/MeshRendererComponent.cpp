#include "MeshRendererComponent.h"

#include "../Rendering/Renderer.h"

MeshRendererComponent::MeshRendererComponent(Mesh& pMesh, Material* pMaterial) :
    _pMesh(pMesh),
    _pMaterial(pMaterial),
    _vertexArrayObject(&pMesh)
{
    _vertexArrayObject.Finalize();
}

Mesh& MeshRendererComponent::GetMesh() const { return _pMesh; }

Material* MeshRendererComponent::GetMaterial() { return _pMaterial; }

VertexArrayObject* MeshRendererComponent::GetVertexArrayObject() { return &_vertexArrayObject; }

void MeshRendererComponent::OnStart()
{
    std::cout << "Start" << std::endl;
    Renderer::Submit(this);
}
