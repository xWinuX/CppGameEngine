#pragma once
#include "GameEngine/Components/PointLight.h"

class RainbowLight final : public GameEngine::Components::Component
{
    private:
        GameEngine::Components::PointLight* _pointLight = nullptr;
    
    public:
        void OnStart() override;
        void OnUpdate() override;
};
