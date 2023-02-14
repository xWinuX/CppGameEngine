#include "GameEngine/Components/MeshRenderer.h"

#include "GameEngine/GameObject.h"
#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;

MeshRenderer::MeshRenderer(Rendering::Mesh* mesh):
    Component("Mesh Renderer"),
    _mesh(mesh) { for (Primitive* primitive : mesh->GetPrimitives()) { _renderablePrimitives.push_back(new RenderablePrimitive(primitive)); } }

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material):
    MeshRenderer(mesh) { for (RenderablePrimitive* renderablePrimitive : _renderablePrimitives) { renderablePrimitive->SetMaterial(material); } }

MeshRenderer::MeshRenderer(Mesh* mesh, const std::initializer_list<Material*> materials, const unsigned int numMaterials):
    MeshRenderer(mesh) { for (unsigned int i = 0; i < numMaterials; i++) { _renderablePrimitives[i]->SetMaterial(*(materials.begin() + 1)); } }

MeshRenderer::~MeshRenderer()
{
    for (const RenderablePrimitive* renderablePrimitive : _renderablePrimitives) { delete renderablePrimitive; }

    _renderablePrimitives.clear();
}

void MeshRenderer::OnComponentAdded() { for (RenderablePrimitive* renderablePrimitive : _renderablePrimitives) { renderablePrimitive->SetTransform(_transform); } }

void MeshRenderer::OnUpdateEnd()
{
    if (!_visible) { return; }

    for (RenderablePrimitive* renderablePrimitive : _renderablePrimitives)
    {
        if (renderablePrimitive->GetMaterial() == nullptr) { Debug::Log::Error("Can't submit a renderable without an material!"); }

        renderablePrimitive->SetLayer(_gameObject->GetLayer());
        Renderer::SubmitRenderable(renderablePrimitive);
    }
}

bool MeshRenderer::GetVisible() const { return _visible; }
void MeshRenderer::SetVisible(const bool value) { _visible = value; }
