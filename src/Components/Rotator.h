#pragma once
#include "GameEngine/Components/Component.h"

class Rotator : public GameEngine::Components::Component
{
    public:
        void OnUpdate() override;
        
};
