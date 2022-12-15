#pragma once
#include <memory>
#include <vector>
#include <glm/vec3.hpp>
#include "../Components/TransformComponent.h"

class GameObject final
{
    private:
        std::vector<Component*> _components;
        TransformComponent*     _transform;
    public:
        GameObject();
        ~GameObject();
        explicit GameObject(glm::vec3 position);

        TransformComponent*      GetTransform() const { return _transform; }
        std::vector<Component*>& GetComponents();

        void AddComponent(Component* component);

        template <typename T>
        T* GetComponent()
        {
            auto foundIterator = std::find_if(_components.begin(), _components.end(), [](const Component* component) { return typeid(*component) == typeid(T); });
            if (foundIterator != _components.end()) { return static_cast<T*>(*foundIterator); }

            return nullptr;
        }


        // template<typename T>
        //void AddComponent();

        virtual void Update() const;
        virtual void LateUpdate() const;
        virtual void PreDraw() const;
        virtual void Draw() const;
        virtual void Start() const;
};
