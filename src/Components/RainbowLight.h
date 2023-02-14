#pragma once
#include "GameEngine/Components/PointLight.h"

class RainbowLight final : public GameEngine::Components::Component
{
    public:
        RainbowLight();
        void OnStart() override;
        void OnUpdate() override;

    private:
        GameEngine::Components::PointLight* _pointLight = nullptr;
};
