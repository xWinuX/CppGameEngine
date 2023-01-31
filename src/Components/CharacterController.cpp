#include "CharacterController.h"

#include "GameEngine/GameObject.h"
#include "GameEngine/Input.h"
#include "GameEngine/Time.h"
#include "glm/gtx/string_cast.hpp"

using namespace GameEngine;

void CharacterController::OnStart()
{
    _rigidbody = _gameObject->GetComponent<GameEngine::Components::Rigidbody>();
    _rigidbody->SetAngularVelocityLockAxisFactor(glm::vec3(0.0, 0.0, 0.0));
}


void CharacterController::OnUpdate()
{
    _velocity = glm::vec3(
                          (float)(Input::GetKeyDown(GLFW_KEY_D) - Input::GetKeyDown(GLFW_KEY_A)) * 500.0f * Time::GetPhysicsDeltaTime(),
                          _rigidbody->GetVelocity().y,
                          (float)(Input::GetKeyDown(GLFW_KEY_S) - Input::GetKeyDown(GLFW_KEY_W)) * 500.0f * Time::GetPhysicsDeltaTime()
                         );

    if (Input::GetKeyPressed(GLFW_KEY_SPACE)) { _jumped = true; }
}

void CharacterController::OnPhysicsUpdate()
{
    const glm::vec3 transformedVelocity = _cameraController->GetTransform()->GetTRS() * glm::vec4(_velocity, 0.0);
    _rigidbody->SetVelocity(glm::vec3(transformedVelocity.x, _velocity.y, transformedVelocity.z));

    if (_jumped)
    {
        _rigidbody->ApplyForce(glm::vec3(0.0f, 300.0f, 0.0f));
        _jumped = false;
    }
}

void CharacterController::SetCameraController(CameraControllerPOV* cameraController) { _cameraController = cameraController; }
