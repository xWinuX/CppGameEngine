#pragma once
#include "Material.h"
#include "GameEngine/Layer.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderable
        {
            public:
                virtual ~Renderable() = default;

                virtual void      OnBeforeDraw();
                virtual void      OnDraw();
                virtual Material* GetMaterial() = 0;

                void  SetLayer(const Layer layer);
                Layer GetLayer() const;

            private:
                Layer _layer = Layer::L_1;
        };
    }
}
