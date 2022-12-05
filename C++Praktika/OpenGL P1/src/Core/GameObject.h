#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include "../Components/Transform.h"

class GameObject
{
    private:
        std::vector<Component> _components;
        Transform              _transform;
    public:
        GameObject();
        explicit GameObject(glm::vec3 position);

        Transform&              GetTransform() { return _transform; }
        std::vector<Component>& GetComponents();

        void Update() const;
        void LateUpdate() const;
        void Draw() const;
};
