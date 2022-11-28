#pragma once

class Component
{
    public:
        virtual ~Component() {}
        virtual void Update() {}
        virtual void LateUpdate() {}
};


