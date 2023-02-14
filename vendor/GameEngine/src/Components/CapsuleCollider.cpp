#include "GameEngine/Components/CapsuleCollider.h"

#include "GameEngine/Physics/PhysicsManager.h"

using namespace GameEngine::Components;
using namespace GameEngine::Physics;


CapsuleCollider::CapsuleCollider(const float radius, const float height):
    Collider("Capsule Collider"),
    _capsuleShape(PhysicsManager::GetPhysicsCommon()->createCapsuleShape(radius, height)),
    _height(height),
    _radius(radius) {}

void CapsuleCollider::OnLateUpdate()
{
    const glm::vec3 scale = _transform->GetLocalScale();
    _capsuleShape->setHeight(_height * scale.y);
    _capsuleShape->setRadius(_radius * (scale.x + scale.z) / 2);
}

CapsuleCollider::~CapsuleCollider()
{
    // Doesn't work for some reason (should have used physx...)
    //PhysicsManager::GetPhysicsCommon()->destroyCapsuleShape(_capsuleShape);
}

reactphysics3d::CollisionShape* CapsuleCollider::GetCollisionShape() { return _capsuleShape; }
