#include "GameEngine/Components/SphereCollider.h"

#include "GameEngine/Physics/PhysicsManager.h"

using namespace GameEngine::Components;

void SphereCollider::OnLateUpdate() { _sphereShape->setRadius(_radius * glm::length(_transform->GetLocalScale())); }

SphereCollider::SphereCollider(const float radius):
    Collider("Sphere Collider"),
    _sphereShape(Physics::PhysicsManager::GetPhysicsCommon()->createSphereShape(radius)),
    _radius(radius) { }

SphereCollider::~SphereCollider()
{
    // Doesn't work for some reason (should have used physx...)
    //Physics::PhysicsManager::GetPhysicsCommon()->destroySphereShape(_sphereShape);
}

reactphysics3d::CollisionShape* SphereCollider::GetCollisionShape() { return _sphereShape; }
