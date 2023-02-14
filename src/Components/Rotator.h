#pragma once
#include "GameEngine/Components/Component.h"

class Rotator : public GameEngine::Components::Component
{
    private:
        float _speed = 10;
    protected:
        void OnUpdate() override;
        void OnGuiDraw() override;
    public:
        Rotator();
        
};
