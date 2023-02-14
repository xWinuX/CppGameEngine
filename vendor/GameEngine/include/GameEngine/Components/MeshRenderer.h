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
                bool _visible = true;

                Rendering::Mesh*                             _mesh = nullptr;
                std::vector<Rendering::RenderablePrimitive*> _renderablePrimitives;

                explicit MeshRenderer(Rendering::Mesh* mesh);

            protected:
                void OnComponentAdded() override;
                void OnUpdateEnd() override;

            public:
                explicit MeshRenderer(Rendering::Mesh* mesh, Rendering::Material* material);
                explicit MeshRenderer(Rendering::Mesh* mesh, std::initializer_list<Rendering::Material*> materials, unsigned int numMaterials);
                ~MeshRenderer() override;


                bool GetVisible() const;
                void SetVisible(const bool value);
            
                void SetMaterial(Rendering::Material* material, size_t index = 0) const;
        };
    }
}
