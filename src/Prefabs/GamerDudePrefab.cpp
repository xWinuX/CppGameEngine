#include "GamerDudePrefab.h"

#include "GameEngine/Components/AudioSource.h"
#include "GameEngine/Components/SpriteRenderer.h"
#include "../Asset.h"
#include "../Components/SimpleWalker.h"
#include "GameEngine/Components/CapsuleCollider.h"
#include "GameEngine/Components/CharacterController.h"
#include "GameEngine/Components/Rigidbody.h"
#include "GameEngine/Components/TextRenderer.h"

using namespace GameEngine;
using namespace GameEngine::Components;


GamerDudePrefab::GamerDudePrefab():
    Prefab("Game Dude") {}

void GamerDudePrefab::PrepareGameObject(GameObject* gameObject)
{
    gameObject->AddComponent(new AudioSource(GET_SOUND(Hey)));
    gameObject->AddComponent(new SpriteRenderer(GET_SPRITE(GamerDudeWalkRight), GET_MATERIAL(SpriteLit)));
    gameObject->AddComponent(new CapsuleCollider(0.5f, 0.87f));
    gameObject->AddComponent(new Rigidbody());
    gameObject->AddComponent(new CharacterController());
    gameObject->AddComponent(new SimpleWalker());

    GameObject* textChild = new GameObject("Text");
    textChild->GetTransform()->SetLocalPosition(glm::vec3(-0.5f, 1.0f, 0.0f));
    textChild->AddComponent(new TextRenderer(GET_FONT(Roboto), GET_MATERIAL(MSDFFont)));
    TextRenderer* textRenderer = textChild->GetComponent<TextRenderer>();
    textRenderer->SetText("Hey!");
    textRenderer->SetAlwaysUpdate(true);
    textChild->SetParent(gameObject);
}
