﻿#pragma once
#include "../Prefabs/CratePrefab.h"
#include "../Prefabs/GamerDudePrefab.h"
#include "GameEngine/Components/Component.h"

class GameManager : public GameEngine::Components::Component
{
    private:
        bool            _fullscreen    = false;
        CratePrefab     _cratePrefab   = CratePrefab();
        GamerDudePrefab _cubeManPrefab = GamerDudePrefab();

    public:
        GameManager();
        void OnUpdate() override;
};
