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
                virtual Texture*     GetTexture() { return nullptr; }
                virtual unsigned int GetVertexSize() { return 0; }
                virtual void         CopyQuadData(unsigned char* destination, unsigned int frameIndex = 0, unsigned int numQuads = 1) { }
        };
    }
}
