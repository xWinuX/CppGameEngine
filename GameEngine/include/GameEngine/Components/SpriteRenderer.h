#pragma once
#include "Component.h"
#include "../Rendering/SpriteSet.h"
#include "../Rendering/Renderable2D.h"
#include "../Rendering/Material.h"

namespace GameEngine
{
    namespace Components
    {
        class SpriteRenderer final : public Component, public Rendering::Renderable2D
        {
            private:
                Rendering::RenderableSprite* _sprite;
                Rendering::Material*         _material;
                float                        _framesPerSecond = 1;
                float                        _frameIndex      = 0;

            protected:
                void OnUpdateEnd() override;
                void OnUpdate() override;

            public:
                SpriteRenderer(Rendering::RenderableSprite* sprite, Rendering::Material* material);

                size_t               GetCopySize() override;
                size_t               GetQuadSize() override;
                void                 CopyQuadData(unsigned char* destination) override;
                void                 OnBeforeDraw() override;
                Rendering::Material* GetMaterial() override;
                Rendering::Texture*  GetTexture() override;

                float GetFrameIndex() const;
                void  SetFrameIndex(float frameIndex);
                void  SetFramesPerSecond(float framesPerSecond);
                void  SetTransform(Components::Transform* transform);
                void  SetSprite(Rendering::RenderableSprite* sprite);
        };
    }
}
