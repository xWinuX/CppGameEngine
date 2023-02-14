#pragma once
#include "Collider.h"
#include "GameEngine/Rendering/Mesh.h"
#include "reactphysics3d/collision/shapes/ConcaveMeshShape.h"

namespace GameEngine
{
    namespace Components
    {
        class MeshCollider : public Collider
        {
            public:
                explicit MeshCollider(Rendering::Mesh* mesh);
                ~MeshCollider() override;
                reactphysics3d::CollisionShape* GetCollisionShape() override;

            private:
                reactphysics3d::ConcaveMeshShape* _concaveMeshShape;
                Rendering::Mesh*                  _mesh;
        };
    }
}
