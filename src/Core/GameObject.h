#pragma once
#include <memory>
#include <vector>
#include <glm/vec3.hpp>
#include "../Components/TransformComponent.h"


namespace GameEngine
{
    namespace Core
    {
        class GameObject final
        {
            private:
                std::vector<GameEngine::Components::Component*> _components;
                GameEngine::Components::TransformComponent*     _transform;

            public:
                GameObject();
                ~GameObject();
                explicit GameObject(glm::vec3 position);

                GameEngine::Components::TransformComponent*      GetTransform() const { return _transform; }
                std::vector<GameEngine::Components::Component*>& GetComponents();

                void AddComponent(GameEngine::Components::Component* component);

                template <typename T>
                T* GetComponent()
                {
                    auto foundIterator = std::find_if(_components.begin(), _components.end(), [](const GameEngine::Components::Component* component)
                    {
                        return typeid(*component) == typeid(T);
                    });
                    if (foundIterator != _components.end()) { return static_cast<T*>(*foundIterator); }

                    return nullptr;
                }

                void OnStart() const;
                void OnUpdate() const;
                void OnLateUpdate() const;
                void OnBeforeRender() const;
        };
    }
}
