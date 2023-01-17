#pragma once
#include "Material.h"
#include "Renderable2D.h"
#include "Sprite.h"
#include "../Components/Transform.h"

namespace GameEngine
{
    namespace Rendering
    {
        class RenderableSprite : public Renderable2D
        {
            private:
                Sprite*                _sprite;
                Material*              _material;
                Components::Transform* _transform       = nullptr;
                float                  _framesPerSecond = 1;
                float                  _frameIndex      = 0;
            public:
                RenderableSprite(Sprite* sprite, Material* material);

                unsigned  GetVertexSize() override;
                void      CopyQuadData(unsigned char* destination) override;
                void      OnBeforeDraw() override;
                Material* GetMaterial() override;
                Texture*  GetTexture() override;

                void Update();

                float GetFrameIndex() const;
                void  SetFrameIndex(float frameIndex);
                void  SetFramesPerSecond(float framesPerSecond);
                void  SetTransform(Components::Transform* transform);
        };
    }
}
