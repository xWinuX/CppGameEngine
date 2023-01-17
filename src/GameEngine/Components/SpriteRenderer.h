#pragma once
#include "Component.h"
#include "../Rendering/Sprite.h"
#include "../Rendering/Material.h"
#include "../Rendering/RenderableSprite.h"

namespace GameEngine
{
    namespace Components
    {
        class SpriteRenderer final : public Component
        {
            private:
                Rendering::Material*         _material;
                Rendering::RenderableSprite* _renderableSprite;
            public:
                SpriteRenderer(Rendering::Sprite* sprite, Rendering::Material* material);
                void OnBeforeRender() override;
                void OnUpdate() override;
                void OnComponentAdded() override;
        };
    }
}
