#pragma once
#include "GameEngine/Prefab.h"

class RigidbodySpherePrefab : public GameEngine::Prefab
{
    protected:
        void PrepareGameObject(GameEngine::GameObject* gameObject) override;

    public:
        RigidbodySpherePrefab();
        
};
