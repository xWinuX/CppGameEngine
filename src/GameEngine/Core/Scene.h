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
                GameObject* _sceneRoot = new GameObject();
            public:
                Scene() = default;
                virtual      ~Scene();
                virtual void InitializeScene() const;
                virtual void Update() const;
                virtual void PhysicsUpdate() const;
                void         AddGameObject(GameObject* gameObject) const;
        };
    }
}
