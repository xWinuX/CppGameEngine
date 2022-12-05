#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include "../Components/TransformComponent.h"

class GameObject
{
    private:
        std::vector<Component> _components;
        TransformComponent     _transform;
    public:
        GameObject();
        explicit GameObject(glm::vec3 position);

        TransformComponent&     GetTransform() { return _transform; }
        std::vector<Component>& GetComponents();

        void AddComponent(const Component& component);

        void Update() const;
        void LateUpdate() const;
        void Draw() const;
};
