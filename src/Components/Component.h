#pragma once

#include "../Core/Transform.h"

namespace GameEngine
{
    namespace Core
    {
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
                GameEngine::Core::GameObject* _gameObject;
                Core::Transform*              _transform;
            public:
                Component():
                    _gameObject(nullptr),
                    _transform(nullptr) {}

                virtual ~Component() = default;

                virtual void OnStart() {}
                virtual void OnUpdate() {}
                virtual void OnPhysicsUpdate() {}
                virtual void OnLateUpdate() {}
                virtual void OnBeforeRender() {}

                virtual void OnComponentAdded() {}
                virtual void OnOtherComponentAdded(Component* component) {}

                const Core::Transform* GetTransform() const { return _transform; }
        };
    }
}
