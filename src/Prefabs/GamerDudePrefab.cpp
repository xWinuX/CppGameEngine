#include "GamerDudePrefab.h"

#include "GameEngine/Components/AudioSource.h"
#include "GameEngine/Components/SpriteRenderer.h"
#include "../Asset.h"
#include "../Components/SimpleWalker.h"

using namespace GameEngine;
using namespace GameEngine::Components;


void GamerDudePrefab::PrepareGameObject(GameObject* gameObject)
{
    gameObject->AddComponent(new AudioSource(GET_SOUND(Hey)));
    gameObject->AddComponent(new SpriteRenderer(GET_SPRITE(GamerDudeWalkRight), GET_MATERIAL(SpriteLit)));
    gameObject->AddComponent(new SimpleWalker());
}
