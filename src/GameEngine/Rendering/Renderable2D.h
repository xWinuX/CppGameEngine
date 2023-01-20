﻿#pragma once
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
                virtual unsigned int GetQuadSize() { return 0; }
                virtual void         CopyQuadData(unsigned char* destination) { }
        };
    }
}