#pragma once

#include <vector>

#include "GameObject.h"

class Scene
{
    private:
        std::vector<GameObject> _gameObjects;
    public:
        virtual void InitializeScene() const;
        virtual void UpdateScene() const;
        void AddGameObject(const GameObject& gameObject);
        
};
