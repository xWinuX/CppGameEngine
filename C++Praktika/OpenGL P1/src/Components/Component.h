#pragma once
#include "../Core/Behaviour.h"
#include "../Core/GameObject.h"

class Component : Behaviour
{
    private:
        GameObject* _gameObject = nullptr;
    public:
        void      AttachToGameObject(GameObject* gameObject);
        Transform GetTransform() const;
        void      Update() override {}
        void      LateUpdate() override {}
        void      Draw() override {}
};
