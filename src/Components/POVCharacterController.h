#pragma once
#include "GameEngine/Components/CharacterController.h"
#include "GameEngine/Components/Component.h"

class POVCharacterController : public GameEngine::Components::Component
{
    public:
        POVCharacterController();
        void OnStart() override;
        void OnUpdate() override;
        void SetCameraTransform(GameEngine::Components::Transform* cameraTransform);

    private:
        GameEngine::Components::CharacterController* _characterController = nullptr;
        GameEngine::Components::Transform*           _cameraTransform;
};
