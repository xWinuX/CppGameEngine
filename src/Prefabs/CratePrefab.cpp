#include "CratePrefab.h"

#include "../Asset.h"
#include "GameEngine/Components/BoxCollider.h"
#include "GameEngine/Components/MeshRenderer.h"
#include "GameEngine/Components/Rigidbody.h"
#include "GameEngine/Components/SpriteRenderer.h"

using namespace GameEngine::Components;

CratePrefab::CratePrefab():
    Prefab("Crate") {}

void CratePrefab::PrepareGameObject(GameEngine::GameObject* gameObject)
{
    gameObject->AddComponent(new MeshRenderer(GET_MODEL(Cube)->GetMesh(0), GET_MATERIAL(Crate)));
    gameObject->AddComponent(new BoxCollider(glm::vec3(0.5f)));
    gameObject->AddComponent(new Rigidbody());
}
