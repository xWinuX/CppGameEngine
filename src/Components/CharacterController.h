#pragma once
#include "CameraControllerPOV.h"
#include "GameEngine/Components/Component.h"
#include "GameEngine/Components/Rigidbody.h"
#include "glm/gtc/constants.hpp"

class CharacterController : public GameEngine::Components::Component
{
    private:
        GameEngine::Components::Rigidbody* _rigidbody        = nullptr;
        CameraControllerPOV*               _cameraController = nullptr;
        glm::vec3                          _velocity         = glm::zero<glm::vec3>();
        bool                               _jumped           = false;

    protected:
        void OnStart() override;
        void OnUpdate() override;
        void OnPhysicsUpdate() override;

    public:
        void SetCameraController(CameraControllerPOV* cameraController);
};
