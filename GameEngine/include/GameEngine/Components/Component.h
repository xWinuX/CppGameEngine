#pragma once

namespace GameEngine
{
    class GameObject;

    namespace Components
    {
        class Transform;

        class Component
        {
            friend GameEngine::GameObject;

            protected:
                GameEngine::GameObject* _gameObject;
                Transform*                    _transform;
                bool                          _enabled = true;
            
                virtual void OnStart();
                virtual void OnUpdate();
                virtual void OnPhysicsUpdate();
                virtual void OnLateUpdate();
                virtual void OnBeforeRender();

                virtual void OnComponentAdded();
                virtual void OnOtherComponentAdded(Component* component);
            
            public:
                Component();
                virtual ~Component() = default;



                void SetEnabled(const bool enabled);
                bool GetEnabled() const;

                const Transform* GetTransform() const;
        };
    }
}
