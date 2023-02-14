#pragma once
#include "Material.h"
#include "Primitive.h"
#include "Renderable.h"
#include "../Components/Transform.h"

namespace GameEngine
{
    namespace Rendering
    {
        class RenderablePrimitive final : public Renderable
        {
            public:
                explicit  RenderablePrimitive(Primitive* primitive, Material* material = nullptr);
                void      OnBeforeDraw() override;
                void      OnDraw() override;
                Material* GetMaterial() override;
                void      SetMaterial(Material* material);
                void      SetTransform(Components::Transform* transform);

            private:
                Primitive*             _primitive;
                Material*              _material;
                Components::Transform* _transform = nullptr;
        };
    }
}
