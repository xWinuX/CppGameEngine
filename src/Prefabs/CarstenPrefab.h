#pragma once
#include "GameEngine/Prefab.h"

class CarstenPrefab : public GameEngine::Prefab
{
    protected:
        void PrepareGameObject(GameEngine::GameObject* gameObject) override;
};
