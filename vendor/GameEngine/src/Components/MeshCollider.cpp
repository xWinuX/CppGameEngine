#include "GameEngine/Components/MeshCollider.h"

#include "GameEngine/Physics/PhysicsManager.h"

GameEngine::Components::MeshCollider::MeshCollider(Rendering::Mesh* mesh):
    Collider("Mesh Collider"),
    _concaveMeshShape(Physics::PhysicsManager::GetPhysicsCommon()->createConcaveMeshShape(mesh->GetColliderMesh())), _mesh(mesh) { }

GameEngine::Components::MeshCollider::~MeshCollider() { }

reactphysics3d::CollisionShape* GameEngine::Components::MeshCollider::GetCollisionShape() { return _concaveMeshShape; }
