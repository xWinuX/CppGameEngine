#include "Scene.h"

void Scene::RunScene() const
{
    for (GameObject gameObject : _gameObjects) { gameObject.Update(); }

    for (GameObject gameObject : _gameObjects) { gameObject.LateUpdate(); }

    for (GameObject gameObject : _gameObjects) { gameObject.Draw(); }
}

void Scene::AddGameObject(const GameObject& gameObject)
{
    _gameObjects.push_back(gameObject);
}
