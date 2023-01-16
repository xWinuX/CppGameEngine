#pragma once
#include "Component.h"
#include "../Rendering/Sprite.h"
#include "../Rendering/Material.h"
#include "../Rendering/Renderable.h"

namespace GameEngine
{
    namespace Components
    {
        class SpriteRenderer final : public Component, public Rendering::Renderable
        {
            private:
                Rendering::Sprite*   _sprite;
                Rendering::Material* _material;
                float                _animationTimer;
            public:
                SpriteRenderer(Rendering::Sprite* sprite, Rendering::Material* material);
                void                 OnBeforeDraw() override;
                void                 OnDraw() override;
                void                 OnBeforeRender() override;
                void                 OnUpdate() override;
                Rendering::Material* GetMaterial() override;
        };
    }
}
