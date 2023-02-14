#include "GameEngine/Components/MeshCollider.h"

#include "GameEngine/Physics/PhysicsManager.h"

GameEngine::Components::MeshCollider::MeshCollider(Rendering::Mesh* mesh):
    Collider("Mesh Collider"),
    _concaveMeshShape(Physics::PhysicsManager::GetPhysicsCommon()->createConcaveMeshShape(mesh->GetColliderMesh())), _mesh(mesh) { }

GameEngine::Components::MeshCollider::~MeshCollider()
{
    // Doesn't work for some reason (should have used physx...)
    //Physics::PhysicsManager::GetPhysicsCommon()->destroyConcaveMeshShape(_concaveMeshShape); 
}

reactphysics3d::CollisionShape* GameEngine::Components::MeshCollider::GetCollisionShape() { return _concaveMeshShape; }
