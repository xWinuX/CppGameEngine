#pragma once

#include <vector>

#include "GameObject.h"

namespace GameEngine
{
    class Scene
    {
        private:
            GameObject* _sceneRoot = new GameObject("Scene Hierarchy");

        public:
            Scene() = default;
            virtual      ~Scene();
            virtual void InitializeScene() const;
            virtual void OnUpdate() const;
            virtual void OnPhysicsUpdate() const;
            virtual void OnPhysicsUpdateEnd(float interpolationFactor) const;
            void         AddGameObject(GameObject* gameObject) const;
    };
}
