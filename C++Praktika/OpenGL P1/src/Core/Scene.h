#pragma once

#include <vector>

#include "GameObject.h"

class Scene
{
    private:
        std::vector<GameObject> _gameObjects;
    public:
        void RunScene() const;
        void AddGameObject(const GameObject& gameObject);
        
};
