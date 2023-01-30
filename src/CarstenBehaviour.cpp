#include "CarstenBehaviour.h"

#include "Asset.h"
#include "GameEngine/GameObject.h"
#include "GameEngine/Time.h"
#include "GameEngine/Rendering/SpriteSet.h"
#include "glm/gtc/random.hpp"
#include "glm/gtx/string_cast.hpp"

using namespace GameEngine::Rendering;

void CarstenBehaviour::OnStart()
{
    _audioSource    = _gameObject->GetComponent<GameEngine::Components::AudioSource>();
    _spriteRenderer = _gameObject->GetComponent<GameEngine::Components::SpriteRenderer>();

    _walkLeftSprite  = GET_SPRITE(CarstenWalkLeft);
    _walkRightSprite = GET_SPRITE(CarstenWalkRight);

    _scale          = _transform->GetLocalScale().x;
    _moveSpeed      = 2.0f / _scale;
    _animationSpeed = 10.0f / _scale;

    RandomizeMoveTimers();
    RandomizeSoundTimer();
}

void CarstenBehaviour::RandomizeMoveTimers()
{
    _canMoveTimer = glm::linearRand(0.70f * _scale, 1.0f * _scale);
    _moveTimer    = glm::linearRand(0.40f * _scale, 0.8f * _scale);
}

void CarstenBehaviour::RandomizeSoundTimer() { _soundTimer = glm::linearRand(3.0f * _scale, 4.0f * _scale); }

void CarstenBehaviour::OnUpdate()
{

    if (_canMoveTimer > 0 && !_canMove) { _canMoveTimer -= GameEngine::Time::GetDeltaTime(); }
    else
    {
        _canMove = true;
        _spriteRenderer->SetSprite(_randomDirection.x > 0 ? _walkRightSprite : _walkLeftSprite);
        _spriteRenderer->SetFramesPerSecond(_animationSpeed);
    }

    if (_canMove)
    {
        if (_moveTimer > 0)
        {
            _transform->MoveLocal((glm::vec3(_randomDirection.x, 0, _randomDirection.y) * _moveSpeed) * GameEngine::Time::GetDeltaTime());
            _moveTimer -= GameEngine::Time::GetDeltaTime();
        }
        else
        {
            _randomDirection = glm::circularRand(1.0f);
            _spriteRenderer->SetFramesPerSecond(0);
            _canMove = false;
            RandomizeMoveTimers();
        }
    }

    if (_soundTimer > 0) { _soundTimer -= GameEngine::Time::GetDeltaTime(); }
    else
    {
        _audioSource->PlayPitch(1 / _transform->GetLocalScale().x);
        RandomizeSoundTimer();
    }
}
