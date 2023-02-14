#include "GameEngine/Components/CharacterController.h"

#include "GameEngine/GameObject.h"
#include "GameEngine/Input.h"
#include "GameEngine/Time.h"
#include "glm/gtx/string_cast.hpp"

using namespace GameEngine::Components;

void CharacterController::OnStart()
{
    _rigidbody = _gameObject->GetComponent<GameEngine::Components::Rigidbody>();
    _rigidbody->SetAngularVelocityLockAxisFactor(glm::vec3(0.0, 0.0, 0.0));
}


void CharacterController::OnPhysicsUpdate()
{
    _rigidbody->SetVelocity(glm::vec3(_moveDirection.x, _rigidbody->GetVelocity().y, _moveDirection.y));

    if (_jumpStrength > 0)
    {
        _rigidbody->ApplyForce(glm::vec3(0.0f, _jumpStrength, 0.0f));
        _jumpStrength = 0;
    }

    _moveDirection = glm::zero<glm::vec2>();
}

CharacterController::CharacterController():
    Component("Character Controller") {}

void CharacterController::Move(const glm::vec2 direction) { _moveDirection = direction * Time::GetPhysicsDeltaTime(); }

void CharacterController::Move(const glm::vec2 direction, const Transform* transform)
{
    const glm::vec4 transformedMove = transform->GetTRS() * glm::vec4(direction.x, 0.0f, direction.y, 0.0);
    Move(glm::vec2(transformedMove.x, transformedMove.z));
}

void CharacterController::Jump(const float strength) { _jumpStrength = strength; }
