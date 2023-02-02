#pragma once
#include "GameEngine/Components/Component.h"

class GameManager : public GameEngine::Components::Component
{
    private:
        bool _showDebugGUI = false; 
    public:
        void OnUpdate() override;
        
};
