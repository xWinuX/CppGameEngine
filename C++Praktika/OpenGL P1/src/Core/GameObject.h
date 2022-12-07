#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include "../Components/TransformComponent.h"

class GameObject
{
    private:
        std::vector<Component*> _components;
        TransformComponent     _transform;
    public:
        GameObject();
        explicit GameObject(glm::vec3 position);

        TransformComponent&     GetTransform() { return _transform; }
        std::vector<Component*>& GetComponents();

        void AddComponent(Component* component);

        virtual void Update() const;
        virtual void LateUpdate() const;
        virtual void PreDraw() const;
        virtual void Draw() const;
        virtual void Start() const;
};
