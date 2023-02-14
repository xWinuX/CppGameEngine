#include "GameEngine/Components/Rigidbody.h"

#include <glm/gtc/quaternion.hpp>

#include "GameEngine/Components/CapsuleCollider.h"
#include "GameEngine/Components/Collider.h"
#include "GameEngine/Physics/PhysicsManager.h"
#include "glm/gtx/vec_swizzle.hpp"

using namespace GameEngine::Physics;
using namespace GameEngine::Components;

Rigidbody::Rigidbody(const reactphysics3d::BodyType bodyType):
    Component("Rigidbody"),
    _physicsRigidBody(PhysicsManager::GetPhysicsWorld()->createRigidBody(reactphysics3d::Transform())) { _physicsRigidBody->setType(bodyType); }

Rigidbody::~Rigidbody() { PhysicsManager::GetPhysicsWorld()->destroyRigidBody(_physicsRigidBody); }

void Rigidbody::OnStart()
{
    const std::vector<Collider*> components = _gameObject->GetComponents<Collider>();
    for (Collider* component : components) { _physicsRigidBody->addCollider(component->GetCollisionShape(), reactphysics3d::Transform()); }
    _physicsRigidBody->setTransform(_transform->GetPhysicsTransform());
}


void Rigidbody::OnPhysicsUpdateEnd(const float interpolationFactor)
{
    const reactphysics3d::Transform currentTransform      = _physicsRigidBody->getTransform();
    const reactphysics3d::Transform interpolatedTransform = reactphysics3d::Transform::interpolateTransforms(_previousTransform, currentTransform, interpolationFactor);

    const reactphysics3d::Vector3    position = interpolatedTransform.getPosition();
    const reactphysics3d::Quaternion rotation = interpolatedTransform.getOrientation();

    const glm::quat quaternion = glm::quat(rotation.w, rotation.x, rotation.y, rotation.z);

    // Don't set rotation if rotation is locked anyway
    if (_physicsRigidBody->getAngularLockAxisFactor().length() > 0.0f) { _transform->SetRotation(quaternion); }

    _transform->SetPosition(glm::vec3(position.x, position.y, position.z));

    _previousTransform = currentTransform;
    
    _physicsRigidBody->setMass(_mass);
}

void Rigidbody::OnOtherComponentAdded(Component* component)
{
    if (typeid(component) == typeid(CapsuleCollider))
    {
        CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(component);
        _physicsRigidBody->addCollider(capsuleCollider->GetCollisionShape(), reactphysics3d::Transform());
    }
}

void Rigidbody::OnGuiDraw() { ImGui::InputFloat(GetImGuiIDString("Mass").c_str(), &_mass); }

void Rigidbody::ResetForce() const { _physicsRigidBody->setLinearVelocity(reactphysics3d::Vector3(0, 0, 0)); }

glm::vec3 Rigidbody::GetVelocity() const
{
    const reactphysics3d::Vector3 velocity = _physicsRigidBody->getLinearVelocity();
    return {velocity.x, velocity.y, velocity.z};
}

void Rigidbody::SetVelocity(const glm::vec3 velocity) const { _physicsRigidBody->setLinearVelocity(reactphysics3d::Vector3(velocity.x, velocity.y, velocity.z)); }

void Rigidbody::ApplyForce(const glm::vec3 force) const { _physicsRigidBody->applyWorldForceAtCenterOfMass(reactphysics3d::Vector3(force.x, force.y, force.z)); }

void Rigidbody::ApplyTorque(const glm::vec3 torque) const { _physicsRigidBody->applyWorldTorque(reactphysics3d::Vector3(torque.x, torque.y, torque.z)); }

void Rigidbody::SetAngularVelocityLockAxisFactor(const glm::vec3 lockAxis) const
{
    _physicsRigidBody->setAngularLockAxisFactor(reactphysics3d::Vector3(lockAxis.x, lockAxis.y, lockAxis.z));
}
