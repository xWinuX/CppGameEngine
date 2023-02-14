#pragma once
#include <string>

#include "GameEngine/ID.h"

namespace GameEngine
{
    class GameObject;

    namespace Components
    {
        class Transform;

        class Component : protected ID
        {
            friend GameEngine::GameObject;

            private:
                bool _initialized = false;
                void SetInitialized(const bool initialized);
            protected:
                const std::string       _name = "NO NAME";
                GameEngine::GameObject* _gameObject;
                Transform*              _transform;
                bool                    _enabled = true;

                virtual void OnStart();
                virtual void OnUpdateBegin();
                virtual void OnUpdate();
                virtual void OnLateUpdate();
                virtual void OnUpdateEnd();
                virtual void OnPhysicsUpdate();
                virtual void OnGuiDraw();

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
                explicit Component(const std::string& name);
                virtual  ~Component() = default;

                std::string GetImGuiName() const;
                void        SetEnabled(const bool enabled);
                bool        GetEnabled() const;
                bool        GetInitialized() const;

                Transform* GetTransform() const;
        };
    }
}
