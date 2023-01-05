#include "CapsuleCollider.h"
#include "../Physics/Physics.h"

GameEngine::Components::CapsuleCollider::CapsuleCollider(const float radius, const float height):
    _pCapsuleShape(Physics::GetPhysicsCommon()->createCapsuleShape(radius, height))
{
}

GameEngine::Components::CapsuleCollider::~CapsuleCollider()
{
    //Physics::GetPhysicsCommon()->destroyCapsuleShape(_pCapsuleShape);
}

reactphysics3d::CollisionShape* GameEngine::Components::CapsuleCollider::GetCollisionShape() { return _pCapsuleShape; }
