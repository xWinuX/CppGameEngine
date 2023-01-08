#include "Rigidbody.h"

#include "CapsuleCollider.h"
#include "../Physics/PhysicsManager.h"
#include <glm/gtc/quaternion.hpp>

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

    const glm::quat quaternion = glm::quat(physicsTransformRotation.w, physicsTransformRotation.x, physicsTransformRotation.y, physicsTransformRotation.z);
    //const glm::vec3 degreesEuler = glm::vec3(glm::degrees(euler.x)-90,glm::degrees(euler.y)-90,glm::degrees(euler.z)-90);

   // Debug::Log::Message(std::to_string(degreesEuler.x) + "," + std::to_string(degreesEuler.y) + "," + std::to_string(degreesEuler.z));
    
    _transform->SetPosition(glm::vec3(physicsTransformPosition.x, physicsTransformPosition.y, physicsTransformPosition.z));
    _transform->SetRotation(quaternion);
}

void GameEngine::Components::Rigidbody::OnOtherComponentAdded(Component* component)
{
    if (typeid(component) == typeid(CapsuleCollider))
    {
        CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(component);
        _pPhysicsRigidBody->addCollider(capsuleCollider->GetCollisionShape(), reactphysics3d::Transform());
    }
}

void GameEngine::Components::Rigidbody::ApplyForce(const glm::vec3 force) const
{
    _pPhysicsRigidBody->applyWorldForceAtCenterOfMass(reactphysics3d::Vector3(force.x, force.y, force.z));
}
