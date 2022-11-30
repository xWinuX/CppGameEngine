#pragma once
#include <vector>
#include <glm/vec3.hpp>

#include "../Components/Component.h"
#include "../Components/Transform.h"

class GameObject : Behaviour
{
    private:
        std::vector<Component> _components;
        Transform              _transform;
    public:
        GameObject();
        explicit GameObject(glm::vec3 position);
    
        Transform&              GetTransform() { return _transform; }
        std::vector<Component>& GetComponents();
    
        void                    Update() override;
        void                    LateUpdate() override;
        void                    Draw() override;
};
