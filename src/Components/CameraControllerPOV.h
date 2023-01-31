#pragma once
#include "GameEngine/Components/Component.h"
#include "reactphysics3d/mathematics/Transform.h"

class CameraControllerPOV : public GameEngine::Components::Component
{
    private:
        GameEngine::Components::Transform* _followTransform = nullptr;

    protected:
        void OnStart() override;
        void OnLateUpdate() override;

    public:
        void SetFollowTransform(GameEngine::Components::Transform* followTransform);
};
