#pragma once

#include <vector>

#include "GameObject.h"

namespace GameEngine
{
    namespace Core
    {
        class Scene
        {
            private:
            std::vector<GameObject*> _gameObjects;
            public:
            Scene() = default;
            virtual ~Scene();
            virtual void InitializeScene() const;
            virtual void Update() const;
            void         AddGameObject(GameObject* gameObject);
        };
    }
}