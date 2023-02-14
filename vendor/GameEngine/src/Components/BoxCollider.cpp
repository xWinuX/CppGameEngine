#include "GameEngine/Components/BoxCollider.h"

#include "GameEngine/Physics/PhysicsManager.h"

using namespace GameEngine;
using namespace GameEngine::Components;
using namespace GameEngine::Physics;

void BoxCollider::OnUpdateEnd()
{
    const glm::vec3 scale = _transform->GetLocalScale();

    const reactphysics3d::Vector3 halfExtends = reactphysics3d::Vector3(
                                                                        _halfExtends.x * scale.x,
                                                                        _halfExtends.y * scale.x,
                                                                        _halfExtends.z * scale.x
                                                                       );

    _boxShape->setHalfExtents(halfExtends);
}

BoxCollider::BoxCollider(const glm::vec3 halfExtends):
    Collider("Box Collider"),
    _boxShape(PhysicsManager::GetPhysicsCommon()->createBoxShape(reactphysics3d::Vector3(halfExtends.x, halfExtends.y, halfExtends.z))),
    _halfExtends(halfExtends) {}

BoxCollider::~BoxCollider()
{
    //Physics::GetPhysicsCommon()->destroyBoxShape(_pBoxShape);
}

reactphysics3d::CollisionShape* BoxCollider::GetCollisionShape() { return _boxShape; }
