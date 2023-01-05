#pragma once
#include "Collider.h"
#include "reactphysics3d/collision/shapes/BoxShape.h"

class BoxCollider : public Collider
{
    private:
        reactphysics3d::BoxShape* _pBoxShape;
    public:
        explicit BoxCollider(glm::vec3 halfExtends);
        ~BoxCollider() override;
        reactphysics3d::CollisionShape* GetCollisionShape() override;
};
