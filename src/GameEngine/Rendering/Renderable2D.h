#pragma once
#include "Renderable.h"
#include "Texture.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderable2D : public Renderable
        {
            public:
                virtual Texture* GetTexture() { return nullptr; }
                virtual size_t   GetQuadSize() { return 0; }
                virtual size_t   GetCopySize() { return 0; }
                virtual void     CopyQuadData(unsigned char* destination) { }
        };
    }
}
