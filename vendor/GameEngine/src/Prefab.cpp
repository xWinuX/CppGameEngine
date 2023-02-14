#include "GameEngine/Prefab.h"

void GameEngine::Prefab::PrepareGameObject(GameObject* gameObject) { }

GameEngine::Prefab::Prefab(const std::string& name):
    _name(name) {}

GameEngine::GameObject* GameEngine::Prefab::Instantiate()
{
    GameObject* gameObject = new GameObject(_name);
    PrepareGameObject(gameObject);
    return gameObject;
}
