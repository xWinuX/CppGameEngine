#include "Rigidbody.h"

#include "CapsuleCollider.h"
#include "../Debug/Log.h"
#include "../Physics/PhysicsManager.h"

using namespace GameEngine::Physics;

GameEngine::Components::Rigidbody::Rigidbody(const reactphysics3d::BodyType bodyType):
    _pPhysicsRigidBody(PhysicsManager::GetPhysicsWorld()->createRigidBody(reactphysics3d::Transform())) { _pPhysicsRigidBody->setType(bodyType); }

GameEngine::Components::Rigidbody::~Rigidbody()
{
    PhysicsManager::GetPhysicsWorld()->destroyRigidBody(_pPhysicsRigidBody);
}

void GameEngine::Components::Rigidbody::OnStart()
{
    const std::vector<Collider*> components = _gameObject->GetComponents<Collider>();
    for (Collider* component : components) { _pPhysicsRigidBody->addCollider(component->GetCollisionShape(), reactphysics3d::Transform()); }
    _pPhysicsRigidBody->setTransform(_transform->GetPhysicsTransform());
}

void GameEngine::Components::Rigidbody::OnPhysicsUpdate()
{
    const reactphysics3d::Transform  physicsTransform         = _pPhysicsRigidBody->getTransform();
    const reactphysics3d::Vector3    physicsTransformPosition = physicsTransform.getPosition();
    const reactphysics3d::Quaternion physicsTransformRotation = physicsTransform.getOrientation();

    const glm::vec3 euler = glm::eulerAngles(glm::quat(physicsTransformRotation.x, physicsTransformRotation.y, physicsTransformRotation.z, physicsTransformRotation.w)); 
    _transform->SetPosition(glm::vec3(physicsTransformPosition.x, physicsTransformPosition.y, physicsTransformPosition.z));
    _transform->SetEulerAngles(glm::degrees(euler));
}

void GameEngine::Components::Rigidbody::OnComponentAdded(Component* component)
{
    if (typeid(component) == typeid(CapsuleCollider))
    {
        CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(component);
        _pPhysicsRigidBody->addCollider(capsuleCollider->GetCollisionShape(), reactphysics3d::Transform());
    }
}
