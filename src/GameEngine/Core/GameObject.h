#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include "../Components/TransformComponent.h"
#include <typeinfo>

#include "../Debug/Log.h"

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

                void AddComponent(GameEngine::Components::Component* addedComponent);

                template <typename T>
                T* GetComponent()
                {
                    auto                                          foundIterator = std::find_if(_components.begin(), _components.end(),
                            [](GameEngine::Components::Component* component) { return dynamic_cast<T*>(component) != nullptr; }
                        );
                    if (foundIterator != _components.end()) { return static_cast<T*>(*foundIterator); }

                    return nullptr;
                }

                template <typename T>
                std::vector<T*> GetComponents()
                {
                    std::vector<GameEngine::Components::Component*> components = std::vector<GameEngine::Components::Component*>();

                    std::copy_if(_components.begin(), _components.end(), std::back_inserter(components), [](GameEngine::Components::Component* component)
                    {
                        return dynamic_cast<T*>(component) != nullptr;
                    });

                    std::vector<T*> castedComponents = std::vector<T*>();

                    for (Components::Component* component : components) { castedComponents.push_back(static_cast<T*>(component)); }

                    return castedComponents;
                }

                void OnStart() const;
                void OnUpdate() const;
                void OnPhysicsUpdate() const;
                void OnLateUpdate() const;
                void OnBeforeRender() const;
        };
    }
}
