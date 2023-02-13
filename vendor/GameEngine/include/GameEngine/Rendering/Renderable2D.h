#pragma once
#include "Renderable.h"
#include "Texture2D.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderable2D : public Renderable
        {
            public:
                virtual Texture2D* GetTexture() { return nullptr; }
                virtual size_t   GetQuadSize() { return 0; }
                virtual size_t   GetCopySize() { return 0; }
                virtual void     CopyQuadData(unsigned char* destination) { }
        };
    }
}
