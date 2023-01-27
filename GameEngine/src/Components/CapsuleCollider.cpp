#include "GameEngine/Components/CapsuleCollider.h"

#include "GameEngine/Physics/Physics.h"

using namespace GameEngine::Components;
using namespace GameEngine::Physics;


CapsuleCollider::CapsuleCollider(const float radius, const float height):
    _pCapsuleShape(Physics::Physics::GetPhysicsCommon()->createCapsuleShape(radius, height))
{
}

CapsuleCollider::~CapsuleCollider()
{
    //Physics::GetPhysicsCommon()->destroyCapsuleShape(_pCapsuleShape);
}

reactphysics3d::CollisionShape* CapsuleCollider::GetCollisionShape() { return _pCapsuleShape; }
