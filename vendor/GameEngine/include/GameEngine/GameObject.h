#pragma once
#include <list>
#include <vector>
#include <glm/vec3.hpp>

#include "ID.h"
#include "Layer.h"
#include "Components/Component.h"
#include "Components/Transform.h"


namespace GameEngine
{
    class Scene;

    class GameObject final : ID
    {
        friend Scene;

        public:
            explicit GameObject(const std::string& name);
            ~GameObject();

            GameEngine::Components::Transform*               GetTransform() const { return _transform; }
            std::vector<GameEngine::Components::Component*>& GetComponents();

            void AddComponent(GameEngine::Components::Component* addedComponent);

            template <typename T>
            T* GetComponent()
            {
                auto foundIterator = std::find_if(_components.begin(), _components.end(), [](GameEngine::Components::Component* component)
                {
                    return dynamic_cast<T*>(component) != nullptr;
                });

                if (foundIterator != _components.end()) { return static_cast<T*>(*foundIterator); }

                return nullptr;
            }

            template <typename T>
            T* GetComponentInChildren()
            {
                T* component = nullptr;
                for (GameObject* child : _children)
                {
                    component = child->GetComponent<T>();
                    if (component != nullptr) { break; }
                }

                return component;
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

            Layer       GetLayer() const;
            GameObject* GetParent() const;

            void SetLayer(Layer layer);
            void SetParent(GameObject* newParent);

        private:
            std::string                                     _name;
            bool                                            _isInitialized           = false;
            GameObject*                                     _parent                  = nullptr;
            Layer                                           _layer                   = Layer::L_1;
            std::list<Components::Component*>               _uninitializedComponents = std::list<Components::Component*>();
            std::list<GameEngine::GameObject*>              _children                = std::list<GameEngine::GameObject*>();
            std::vector<GameEngine::Components::Component*> _components;
            GameEngine::Components::Transform*              _transform;

            void AddChild(GameObject* child);
            void RemoveChild(GameObject* child);

            void OnStart();
            void OnUpdateBegin() const;
            void OnUpdate() const;
            void OnLateUpdate() const;
            void OnUpdateEnd() const;
            void OnPhysicsUpdate() const;
            void OnPhysicsUpdateEnd(float interpolationFactor) const;
            void OnDrawGui() const;
    };
}
