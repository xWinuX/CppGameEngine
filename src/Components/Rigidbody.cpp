#include "Rigidbody.h"

#include "CapsuleCollider.h"
#include "../Debug/Log.h"
#include "../Physics/Physics.h"

GameEngine::Components::Rigidbody::Rigidbody(reactphysics3d::BodyType bodyType):
    _pPhysicsRigidBody(Physics::GetPhysicsWorld()->createRigidBody(reactphysics3d::Transform()))
{
    _pPhysicsRigidBody->setType(bodyType);
}

GameEngine::Components::Rigidbody::~Rigidbody()
{
    //Physics::GetPhysicsWorld()->destroyRigidBody(_pPhysicsRigidBody);
}

void GameEngine::Components::Rigidbody::OnStart()
{
    const std::vector<Collider*> components = _gameObject->GetComponents<Collider>();
    Debug::Log::Message(std::to_string(components.size()));
    for (Collider* component : components) { _pPhysicsRigidBody->addCollider(component->GetCollisionShape(), _transform->GetPhysicsTransform()); }
    _pPhysicsRigidBody->setTransform(_transform->GetPhysicsTransform());
}

void GameEngine::Components::Rigidbody::OnPhysicsUpdate()
{
    const reactphysics3d::Transform physicsTransform         = _pPhysicsRigidBody->getTransform();
    const reactphysics3d::Vector3   physicsTransformPosition = physicsTransform.getPosition();
    const reactphysics3d::Quaternion   physicsTransformRotation = physicsTransform.getOrientation();

    //glm::vec3 euler = glm::eulerAngles(glm::quat(physicsTransformRotation.x, physicsTransformRotation.y, physicsTransformRotation.z, physicsTransformRotation.w)); 
    
    Debug::Log::Message(physicsTransformPosition.to_string());
    _transform->SetPosition(glm::vec3(physicsTransformPosition.x, physicsTransformPosition.y, physicsTransformPosition.z));
    //_transform->SetEulerAngles(glm::degrees(euler));
}

void GameEngine::Components::Rigidbody::OnComponentAdded(Component* component)
{
    if (typeid(component) == typeid(CapsuleCollider))
    {
        CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(component);
        _pPhysicsRigidBody->addCollider(capsuleCollider->GetCollisionShape(), _transform->GetPhysicsTransform());
    }
}
