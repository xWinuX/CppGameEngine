#pragma once
#include "GameEngine/Prefab.h"

class RigidbodySpherePrefab : public GameEngine::Prefab
{
    public:
        RigidbodySpherePrefab();

    protected:
        void PrepareGameObject(GameEngine::GameObject* gameObject) override;
};
