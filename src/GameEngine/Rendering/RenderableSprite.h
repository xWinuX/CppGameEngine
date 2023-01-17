#pragma once
#include "Material.h"
#include "Renderable2D.h"
#include "Sprite.h"

namespace GameEngine
{
    namespace Rendering
    {
        class RenderableSprite : public Renderable2D
        {
            private:
                Sprite*   _sprite;
                Material* _material;
            public:
                RenderableSprite(Sprite* sprite, Material* material);
                unsigned GetVertexSize() override;
                void CopyQuadData(unsigned char* destination, unsigned frameIndex, unsigned numQuads) override;
        };
    }
}
