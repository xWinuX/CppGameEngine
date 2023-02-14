#pragma once
#include "GameEngine/Components/Component.h"

class Rotator : public GameEngine::Components::Component
{
    public:
        Rotator();

    protected:
        void OnUpdate() override;
        void OnGuiDraw() override;

    private:
        float _speed = 10;
};
