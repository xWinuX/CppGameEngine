#pragma once
#include "Collider.h"
#include "reactphysics3d/collision/shapes/CapsuleShape.h"


namespace GameEngine
{
    namespace Components
    {
        class CapsuleCollider final : public Collider
        {
            private:
                reactphysics3d::CapsuleShape* _capsuleShape;
                float                         _height;
                float                         _radius;

            protected:
                void OnLateUpdate() override;

            public:
                explicit CapsuleCollider(float radius = 1.0f, float height = 2.0f);
                ~CapsuleCollider() override;
                reactphysics3d::CollisionShape* GetCollisionShape() override;
        };
    }
}
