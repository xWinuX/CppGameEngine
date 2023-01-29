#include "CarstenBehaviour.h"

#include "GameEngine/GameObject.h"
#include "GameEngine/Time.h"
#include "glm/gtc/random.hpp"
#include "glm/gtx/string_cast.hpp"

void CarstenBehaviour::OnStart()
{
    _audioSource    = _gameObject->GetComponent<GameEngine::Components::AudioSource>();
    _spriteRenderer = _gameObject->GetComponent<GameEngine::Components::SpriteRenderer>();
}

void CarstenBehaviour::OnUpdate()
{
    if (_canMoveTimer > 0) { _canMoveTimer -= GameEngine::Time::GetDeltaTime(); }
    else { _canMove = true; }

    if (_canMove)
    {
        if (_moveTimer > 0)
        {
            _spriteRenderer->SetFramesPerSecond(10.0f / length(_transform->GetLocalScale()));

            GameEngine::Debug::Log::Error(glm::to_string(_randomDirection));
            _transform->MoveLocal((glm::vec3(_randomDirection.x, 0, _randomDirection.y) * _moveSpeed) * GameEngine::Time::GetDeltaTime());

            _moveTimer -= GameEngine::Time::GetDeltaTime();
        }
        else
        {
            _randomDirection = glm::circularRand(1.0f);
            _spriteRenderer->SetFramesPerSecond(0);
            _canMove = false;
            _canMoveTimer = 2;
            _moveTimer = 2;
            _audioSource->Play();
        }
    }
}
