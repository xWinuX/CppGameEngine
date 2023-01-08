#include "MeshRenderer.h"

#include "../Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;


MeshRenderer::RenderableMeshPrimitive::RenderableMeshPrimitive(const Rendering::Mesh::Primitive primitive, Rendering::Material* material):
    Rendering::RenderableMeshPrimitive(primitive, material) {}

void MeshRenderer::RenderableMeshPrimitive::OnBeforeDraw()
{
    const glm::mat4 trs = _transform->GetTRS();
    _material->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_Transform", trs);
}

void MeshRenderer::RenderableMeshPrimitive::SetTransform(Core::Transform* transform) { _transform = transform; }

MeshRenderer::MeshRenderer(GameEngine::Rendering::Mesh* mesh):
    _mesh(mesh) { for (const Mesh::Primitive& subMesh : _mesh->GetSubMeshes()) { _renderableMeshPrimitives.push_back(new RenderableMeshPrimitive(subMesh)); } }

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material):
    MeshRenderer(mesh) { for (Rendering::RenderableMeshPrimitive* renderableMeshPrimitive : _renderableMeshPrimitives) { renderableMeshPrimitive->SetMaterial(material); } }

MeshRenderer::MeshRenderer(GameEngine::Rendering::Mesh* mesh, GameEngine::Rendering::Material** materials, const unsigned int numMaterials):
    MeshRenderer(mesh)
{
    if (numMaterials != _renderableMeshPrimitives.size()) { Debug::Log::Error("You must pass the same amount of materials as there are mesh primitives!"); }

    for (unsigned int i = 0; i < numMaterials; i++) { _renderableMeshPrimitives[i]->SetMaterial(materials[i]); }
}

MeshRenderer::~MeshRenderer()
{
    for (const Rendering::RenderableMeshPrimitive* renderableMeshPrimitive : _renderableMeshPrimitives) { delete renderableMeshPrimitive; }

    _renderableMeshPrimitives.clear();
}

void MeshRenderer::OnComponentAdded() { for (RenderableMeshPrimitive* renderableMeshPrimitive : _renderableMeshPrimitives) { renderableMeshPrimitive->SetTransform(_transform); } }

void MeshRenderer::OnBeforeRender()
{
    if (!_visible) { return; }

    for (RenderableMeshPrimitive* renderableMeshPrimitive : _renderableMeshPrimitives)
    {
        if (renderableMeshPrimitive->GetMaterial() == nullptr) { Debug::Log::Error("Can't submit a renderable without an material!"); }

        Renderer::SubmitRenderable(renderableMeshPrimitive);
    }
}

bool MeshRenderer::GetVisible() const { return _visible; }
void MeshRenderer::SetVisible(const bool value) { _visible = value; }
