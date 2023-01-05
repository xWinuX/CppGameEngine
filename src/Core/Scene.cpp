#include "Scene.h"

using namespace GameEngine::Core;


Scene::~Scene()
{
    for (const GameObject* gameObject : _gameObjects)
    {
        delete gameObject;
    }
}

void Scene::InitializeScene() const { for (const GameObject* gameObject : _gameObjects) { gameObject->OnStart(); } }

void Scene::Update() const
{
    for (const GameObject* gameObject : _gameObjects) { gameObject->OnUpdate(); }
    
    for (const GameObject* gameObject : _gameObjects) { gameObject->OnLateUpdate(); }

    for (const GameObject* gameObject : _gameObjects) { gameObject->OnBeforeRender(); }
}

void Scene::PhysicsUpdate() const
{
    for (const GameObject* gameObject : _gameObjects) { gameObject->OnPhysicsUpdate(); }

}

void Scene::AddGameObject(GameObject* gameObject) { _gameObjects.push_back(gameObject); }
