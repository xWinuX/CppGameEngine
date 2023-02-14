#pragma once
#include "Collider.h"
#include "reactphysics3d/collision/shapes/CapsuleShape.h"


namespace GameEngine
{
    namespace Components
    {
        class CapsuleCollider final : public Collider
        {
            public:
                explicit CapsuleCollider(float radius = 1.0f, float height = 2.0f);
                ~CapsuleCollider() override;
                reactphysics3d::CollisionShape* GetCollisionShape() override;

            protected:
                void OnLateUpdate() override;

            private:
                reactphysics3d::CapsuleShape* _capsuleShape;
                float                         _height;
                float                         _radius;
        };
    }
}
