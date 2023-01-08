#pragma once
#include "GameEngine/Core/Application.h"

class GraphicDemoApplication : public Application
{
    public:
        void Initialize(GameEngine::Core::Scene& scene) override;
        void CustomRun() override;
        
};
