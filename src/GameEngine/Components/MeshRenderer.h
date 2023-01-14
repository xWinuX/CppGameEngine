#pragma once
#include "Component.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Material.h"
#include "../Rendering/RenderablePrimitive.h"

namespace GameEngine
{
    namespace Components
    {
        class MeshRenderer final : public Component
        {
            private:
                Rendering::Mesh*                             _mesh;
                std::vector<Rendering::RenderablePrimitive*> _renderablePrimitives;

                bool _visible = true;
                explicit MeshRenderer(Rendering::Mesh* mesh);
            public:
                explicit MeshRenderer(Rendering::Mesh* mesh, Rendering::Material* material);
                explicit MeshRenderer(Rendering::Mesh* mesh, std::initializer_list<Rendering::Material*> materials, unsigned int numMaterials);
                ~MeshRenderer() override;
                void OnComponentAdded() override;
                void OnBeforeRender() override;

                bool GetVisible() const;
                void SetVisible(const bool value);
        };
    }
}
