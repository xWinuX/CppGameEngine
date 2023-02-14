﻿#pragma once
#include "Collider.h"
#include "glm/vec3.hpp"
#include "reactphysics3d/collision/shapes/BoxShape.h"


namespace GameEngine
{
    namespace Components
    {
        class BoxCollider : public Collider
        {
            private:
                reactphysics3d::BoxShape* _boxShape;
                glm::vec3 _halfExtends;

            protected:
                void OnUpdateEnd() override;
            
            public:
                explicit BoxCollider(glm::vec3 halfExtends);
                ~BoxCollider() override;
                reactphysics3d::CollisionShape* GetCollisionShape() override;
        };
    }
}