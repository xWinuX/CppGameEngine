#include "GameEngine/Prefab.h"

void GameEngine::Prefab::PrepareGameObject(GameObject* gameObject) { }

GameEngine::Prefab::Prefab(const std::string& name):
    _name(name) {}

GameEngine::GameObject* GameEngine::Prefab::Instantiate() { return Instantiate(glm::zero<glm::vec3>()); }

GameEngine::GameObject* GameEngine::Prefab::Instantiate(const glm::vec3 position)
{
    GameObject* gameObject = new GameObject(_name);
    gameObject->GetTransform()->SetLocalPosition(position);
    PrepareGameObject(gameObject);
    return gameObject;
}
