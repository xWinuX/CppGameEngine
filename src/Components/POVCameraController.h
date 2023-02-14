#pragma once
#include "GameEngine/Components/CharacterController.h"
#include "GameEngine/Components/Component.h"
#include "glm/vec2.hpp"
#include "glm/gtc/constants.hpp"
#include "reactphysics3d/mathematics/Transform.h"

class POVCameraController : public GameEngine::Components::Component
{
    private:
        GameEngine::Components::Transform* _followTransform = nullptr;
        glm::vec2 _currentAngle = glm::zero<glm::vec2>();
        glm::vec2 _previousMousePosition = glm::zero<glm::vec2>();
        float _mouseSpeed = 0.005f;

    protected:
        void OnLateUpdate() override;

    public:
        POVCameraController();
        void SetFollowTransform(GameEngine::Components::Transform* followTransform);
};
