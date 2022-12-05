#pragma once

class Component
{
    public:
        virtual   ~Component() = default;

        virtual void OnUpdate() {}
        virtual void OnLateUpdate() {}
        virtual void OnDraw() {}
};
