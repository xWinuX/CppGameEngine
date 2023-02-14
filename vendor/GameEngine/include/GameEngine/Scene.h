#pragma once

#include "GameObject.h"

namespace GameEngine
{
    class Scene
    {
        friend class GameObject;

        public:
            Scene();
            virtual      ~Scene();
            void         Bind();
            virtual void OnUpdate();
            virtual void OnPhysicsUpdate() const;
            virtual void OnPhysicsUpdateEnd(float interpolationFactor) const;

        private:
            GameObject*            _sceneRoot                = nullptr;
            std::list<GameObject*> _uninitializedGameObjects = std::list<GameObject*>();
            static Scene*          _currentScene;
            static Scene*          GetCurrentScene();
            void                   AddGameObject(GameObject* gameObject);
    };
}
