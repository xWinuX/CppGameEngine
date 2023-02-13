#include "GameEngine/Components/CapsuleCollider.h"

#include "GameEngine/Physics/PhysicsManager.h"

using namespace GameEngine::Components;
using namespace GameEngine::Physics;


CapsuleCollider::CapsuleCollider(const float radius, const float height):
    _height(height),
    _radius(radius),
    _pCapsuleShape(PhysicsManager::GetPhysicsCommon()->createCapsuleShape(radius, height)) {}

void CapsuleCollider::OnLateUpdate()
{
    const glm::vec3 scale = _transform->GetLocalScale();
    _pCapsuleShape->setHeight(_height * scale.y);
    _pCapsuleShape->setRadius(_radius * (scale.x + scale.z)/2);
}

CapsuleCollider::~CapsuleCollider()
{
    //Physics::GetPhysicsCommon()->destroyCapsuleShape(_pCapsuleShape);
}

reactphysics3d::CollisionShape* CapsuleCollider::GetCollisionShape() { return _pCapsuleShape; }
