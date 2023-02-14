#pragma once
#include "GameEngine/Components/Collider.h"
#include "reactphysics3d/collision/shapes/SphereShape.h"

namespace GameEngine
{
    namespace Components
    {
        class SphereCollider : public Collider
        {
            private:
                reactphysics3d::SphereShape* _sphereShape;
                float                        _radius;

            protected:
                void OnLateUpdate() override;
            public:
                explicit SphereCollider(float radius);
                ~SphereCollider() override;
                reactphysics3d::CollisionShape* GetCollisionShape() override;
        };
    }
}
