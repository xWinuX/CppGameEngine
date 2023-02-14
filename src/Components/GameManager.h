#pragma once
#include "GameEngine/Components/Component.h"

class GameManager : public GameEngine::Components::Component
{
    private:
        bool _showDebugGUI = false;
        bool _fullscreen = false;
    public:
        GameManager();
        void OnUpdate() override;
        
};
