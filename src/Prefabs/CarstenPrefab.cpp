#include "CarstenPrefab.h"

#include "GameEngine/Components/AudioSource.h"
#include "GameEngine/Components/SpriteRenderer.h"
#include "../Asset.h"
#include "../CarstenBehaviour.h"

using namespace GameEngine;
using namespace GameEngine::Components;


void CarstenPrefab::PrepareGameObject(GameObject* gameObject)
{
    gameObject->AddComponent(new AudioSource(GET_SOUND(Hey)));
    gameObject->AddComponent(new SpriteRenderer(GET_SPRITE(CarstenWalkRight), GET_MATERIAL(SpriteLit)));
    gameObject->AddComponent(new CarstenBehaviour());
}
