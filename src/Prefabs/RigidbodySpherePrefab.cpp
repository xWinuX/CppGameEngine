#include "RigidbodySpherePrefab.h"

#include "GameEngine/Components/MeshRenderer.h"
#include "GameEngine/Components/Rigidbody.h"
#include "GameEngine/Components/SphereCollider.h"

using namespace GameEngine::Components;


RigidbodySpherePrefab::RigidbodySpherePrefab():
    Prefab("Rigidbody Sphere") {}

void RigidbodySpherePrefab::PrepareGameObject(GameEngine::GameObject* gameObject)
{
    gameObject->AddComponent(new MeshRenderer(GET_MODEL(Sphere)->GetMesh(0), GET_MATERIAL(Porcelain)));
    gameObject->AddComponent(new SphereCollider(0.5f));
    gameObject->AddComponent(new Rigidbody());
}
