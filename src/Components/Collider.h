#pragma once
#include "Component.h"
#include "reactphysics3d/collision/shapes/CollisionShape.h"


class Collider : public GameEngine::Components::Component
{
    public:
        virtual reactphysics3d::CollisionShape* GetCollisionShape() = 0;
};
