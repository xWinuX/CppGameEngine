#pragma once

class Renderable
{
    public:
        virtual ~Renderable() = default;
    
        virtual void OnBeforeDraw() {}
        virtual void OnDraw() {}

        virtual Material* GetMaterial() { return nullptr; }
};
