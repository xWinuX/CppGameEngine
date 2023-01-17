#pragma once
#include "Component.h"
#include "../Rendering/Sprite.h"
#include "../Rendering/Renderable2D.h"
#include "../Rendering/Material.h"

namespace GameEngine
{
    namespace Components
    {
        class SpriteRenderer final : public Component, public Rendering::Renderable2D
        {
            private:
                Rendering::Sprite*   _sprite;
                Rendering::Material* _material;
                float                _framesPerSecond = 1;
                float                _frameIndex      = 0;
            public:
                SpriteRenderer(Rendering::Sprite* sprite, Rendering::Material* material);

                void OnBeforeRender() override;
                void OnUpdate() override;

                unsigned             GetVertexSize() override;
                void                 CopyQuadData(unsigned char* destination) override;
                void                 OnBeforeDraw() override;
                Rendering::Material* GetMaterial() override;
                Rendering::Texture*  GetTexture() override;

                float GetFrameIndex() const;
                void  SetFrameIndex(float frameIndex);
                void  SetFramesPerSecond(float framesPerSecond);
                void  SetTransform(Components::Transform* transform);
        };
    }
}
