#pragma once
#include "GameEngine/Application.h"

class GraphicDemoApplication final : public GameEngine::Application
{
    public:
        void Initialize(GameEngine::Scene& scene) override;
        void CustomRun() override;
};
