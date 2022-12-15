#include "Scene.h"

#include <iostream>

Scene::~Scene()
{
    for (const GameObject* gameObject : _gameObjects)
    {
        delete gameObject;
    }
}

void Scene::InitializeScene() const { for (const GameObject* gameObject : _gameObjects) { gameObject->Start(); } }

void Scene::Update() const
{
    for (const GameObject* gameObject : _gameObjects) { gameObject->Update(); }

    for (const GameObject* gameObject : _gameObjects) { gameObject->LateUpdate(); }

    for (const GameObject* gameObject : _gameObjects) { gameObject->PreDraw(); }

    for (const GameObject* gameObject : _gameObjects) { gameObject->Draw(); }
}

void Scene::AddGameObject(GameObject* gameObject) { _gameObjects.push_back(gameObject); }
