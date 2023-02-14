#pragma once
#include "Component.h"
#include "reactphysics3d/collision/shapes/CollisionShape.h"


class Collider : public GameEngine::Components::Component
{
    public:
        Collider(const std::string& name);
        virtual reactphysics3d::CollisionShape* GetCollisionShape() = 0;
};

inline Collider::Collider(const std::string& name):
    Component(name) {}
