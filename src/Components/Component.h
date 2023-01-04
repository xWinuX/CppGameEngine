#pragma once

#include "../Core/Transform.h"

namespace GameEngine
{
    namespace Core {
        class GameObject;
    }
}

namespace GameEngine
{
    namespace Components
    {

        class Component
        {
            friend GameEngine::Core::GameObject;

            protected:
            const GameEngine::Core::GameObject* _gameObject;
            const Core::Transform*  _transform;

            public:
            Component():
                _gameObject(nullptr),
                _transform(nullptr) {}

            virtual ~Component() = default;

            virtual void OnStart() {}
            virtual void OnUpdate() {}
            virtual void OnLateUpdate() {}
            virtual void OnBeforeRender() {}

            const Core::Transform* GetTransform() const { return _transform; }
        };
    }
}
