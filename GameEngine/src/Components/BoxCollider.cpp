#include "GameEngine/Components/BoxCollider.h"

#include "GameEngine/Physics/Physics.h"

using namespace GameEngine::Components;
using namespace GameEngine::Physics;

BoxCollider::BoxCollider(const glm::vec3 halfExtends):
    _pBoxShape(Physics::Physics::GetPhysicsCommon()->createBoxShape(reactphysics3d::Vector3(halfExtends.x, halfExtends.y, halfExtends.z))) {}

BoxCollider::~BoxCollider()
{
    //Physics::GetPhysicsCommon()->destroyBoxShape(_pBoxShape);
}

reactphysics3d::CollisionShape* BoxCollider::GetCollisionShape() { return _pBoxShape; }
