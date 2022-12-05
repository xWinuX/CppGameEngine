#pragma once

#include "../Core/Transform.h"

class Component
{
    private:
        const Transform* _transform;
    public:
        Component(): _transform(nullptr) {}
        virtual   ~Component() = default;

        virtual void OnUpdate() {}
        virtual void OnLateUpdate() {}
        virtual void OnDraw() {}

        void SetTransform(const Transform* transform) {_transform = transform;}
        const Transform* GetTransform() const {return _transform;}
};
