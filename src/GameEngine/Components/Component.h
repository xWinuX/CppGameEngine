#pragma once

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
        class Transform;

        class Component
        {
            friend GameEngine::Core::GameObject;

            protected:
                GameEngine::Core::GameObject* _gameObject;
                Transform*                    _transform;
                bool                          _enabled = true;

            public:
                Component();
                virtual ~Component() = default;

                virtual void OnStart();
                virtual void OnUpdate();
                virtual void OnPhysicsUpdate();
                virtual void OnLateUpdate();
                virtual void OnBeforeRender();

                virtual void OnComponentAdded();
                virtual void OnOtherComponentAdded(Component* component);

                void SetEnabled(const bool enabled);
                bool GetEnabled() const;

                const Transform* GetTransform() const;
        };
    }
}
