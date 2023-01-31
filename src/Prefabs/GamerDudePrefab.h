#pragma once
#include "GameEngine/Prefab.h"

class GamerDudePrefab : public GameEngine::Prefab
{
    protected:
        void PrepareGameObject(GameEngine::GameObject* gameObject) override;
};
