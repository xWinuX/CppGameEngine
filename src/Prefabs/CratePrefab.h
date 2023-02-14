#pragma once
#include "GameEngine/Prefab.h"

class CratePrefab : public GameEngine::Prefab
{
    public:
        CratePrefab();

    protected:
        void PrepareGameObject(GameEngine::GameObject* gameObject) override;
        
};
