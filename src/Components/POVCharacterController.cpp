#include "POVCharacterController.h"

#include "GameEngine/Input.h"
#include "GameEngine/Components/CharacterController.h"
#include "glm/vec2.hpp"

using namespace GameEngine;
using namespace GameEngine::Components;

POVCharacterController::POVCharacterController():
    Component("POV Character Controller") {}

void POVCharacterController::OnStart() { _characterController = _gameObject->GetComponent<CharacterController>(); }

void POVCharacterController::OnUpdate()
{
    float           speed   = Input::GetKeyDown(GLFW_KEY_LEFT_SHIFT) ? 2000.0f : 1000.0f;
    const glm::vec2 walkDir = glm::vec2(
                                        static_cast<float>(Input::GetKeyDown(GLFW_KEY_D) - Input::GetKeyDown(GLFW_KEY_A)) * speed,
                                        static_cast<float>(Input::GetKeyDown(GLFW_KEY_S) - Input::GetKeyDown(GLFW_KEY_W)) * speed
                                       );

    if (GameEngine::Input::GetKeyPressed(GLFW_KEY_SPACE)) { _characterController->Jump(1000); }

    _characterController->Move(walkDir, _cameraTransform);
}

void POVCharacterController::SetCameraTransform(GameEngine::Components::Transform* cameraTransform) { _cameraTransform = cameraTransform; }
