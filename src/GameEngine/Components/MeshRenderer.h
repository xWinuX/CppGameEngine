#pragma once
#include "Component.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Material.h"
#include "../Rendering/RenderableMeshPrimitive.h"

namespace GameEngine
{
    namespace Components
    {
        class MeshRenderer final : public Component
        {
            private:
                class RenderableMeshPrimitive final : public Rendering::RenderableMeshPrimitive
                {
                    private:
                        Transform* _transform = nullptr;
                    public:
                        explicit RenderableMeshPrimitive(const Rendering::Mesh::Primitive primitive, Rendering::Material* material = nullptr);
                        void     OnBeforeDraw() override;
                        void     SetTransform(Transform* transform);
                };

                GameEngine::Rendering::Mesh*          _mesh;
                std::vector<RenderableMeshPrimitive*> _renderableMeshPrimitives;

                bool _visible = true;
            public:
                explicit MeshRenderer(GameEngine::Rendering::Mesh* mesh);
                explicit MeshRenderer(GameEngine::Rendering::Mesh* mesh, GameEngine::Rendering::Material* material);
                explicit MeshRenderer(GameEngine::Rendering::Mesh* mesh, std::initializer_list<GameEngine::Rendering::Material*> materials, unsigned int numMaterials);

                ~MeshRenderer() override;

                void OnComponentAdded() override;
                void OnBeforeRender() override;

                bool GetVisible() const;
                void SetVisible(const bool value);
        };
    }
}
