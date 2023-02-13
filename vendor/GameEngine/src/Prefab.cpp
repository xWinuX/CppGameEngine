#include "GameEngine/Prefab.h"

void GameEngine::Prefab::PrepareGameObject(GameObject* gameObject) { }

GameEngine::GameObject* GameEngine::Prefab::Instantiate()
{
    GameObject* gameObject = new GameObject();
    PrepareGameObject(gameObject);
    return gameObject;
}
