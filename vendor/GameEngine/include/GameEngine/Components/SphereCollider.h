#pragma once
#include "GameEngine/Components/Collider.h"
#include "reactphysics3d/collision/shapes/SphereShape.h"

namespace GameEngine
{
    namespace Components
    {
        class SphereCollider : public Collider
        {
            public:
                explicit SphereCollider(float radius);
                ~SphereCollider() override;
                reactphysics3d::CollisionShape* GetCollisionShape() override;

            protected:
                void OnLateUpdate() override;

            private:
                reactphysics3d::SphereShape* _sphereShape;
                float                        _radius;
        };
    }
}
