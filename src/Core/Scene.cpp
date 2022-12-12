#include "Scene.h"

#include <iostream>

void Scene::InitializeScene() const
{
    std::cout << "init scene" << std::endl;
    for (const GameObject& gameObject : _gameObjects)
    {
        std::cout << "start gameobjects" << std::endl;
        gameObject.Start();
    }
}

void Scene::Update() const
{
    for (const GameObject& gameObject : _gameObjects) { gameObject.Update(); }

    for (const GameObject& gameObject : _gameObjects) { gameObject.LateUpdate(); }

    for (const GameObject& gameObject : _gameObjects) { gameObject.PreDraw(); }
    
    for (const GameObject& gameObject : _gameObjects) { gameObject.Draw(); }
}

void Scene::AddGameObject(const GameObject& gameObject)
{
    std::cout << "Add gameobject" << std::endl;
    _gameObjects.push_back(gameObject);
}
