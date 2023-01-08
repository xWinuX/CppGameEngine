#pragma once

namespace GameEngine
{
    namespace Rendering
    {
        class Renderable
        {
            public:
                virtual ~Renderable() = default;
        
                virtual void OnBeforeDraw() {}
                virtual void OnDraw() {}

                virtual Material* GetMaterial() { return nullptr; }
        };
    }
}