#pragma once
#include "GameEngine/Prefab.h"

class GamerDudePrefab : public GameEngine::Prefab
{
    public:
        GamerDudePrefab();

    protected:
        void PrepareGameObject(GameEngine::GameObject* gameObject) override;
};
