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
                Transform*              _transform;
                bool                    _enabled = true;
            
                virtual void OnStart();
                virtual void OnUpdateBegin();
                virtual void OnUpdate();
                virtual void OnLateUpdate();
                virtual void OnUpdateEnd();
                virtual void OnPhysicsUpdate();
            
                /**
                 * \brief
                 * Runs at the end of a physics update cycle
                 * \n \n
                 * IMPORTANT: This only runs once for each object even if they were multiple physics updates per frame
                 * \param interpolationFactor (accumulator/timeStep)
                 */
                virtual void OnPhysicsUpdateEnd(float interpolationFactor);

                virtual void OnComponentAdded();
                virtual void OnOtherComponentAdded(Component* component);

            public:
                Component();
                virtual ~Component() = default;


                void SetEnabled(const bool enabled);
                bool GetEnabled() const;

                Transform* GetTransform() const;
        };
    }
}
