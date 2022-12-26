#pragma once

#include "../Core/Transform.h"

class GameObject;

class Component
{
    friend GameObject;

    protected:
        const GameObject* _gameObject;
        const Transform*  _transform;

    public:
        Component():
            _gameObject(nullptr),
            _transform(nullptr) {}

        virtual ~Component() = default;

        virtual void OnStart() {}
        virtual void OnUpdate() {}
        virtual void OnLateUpdate() {}
        virtual void OnBeforeRender() {}

        const Transform* GetTransform() const { return _transform; }
};
