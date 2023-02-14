#include "SimpleWalker.h"

#include "../Asset.h"
#include "GameEngine/GameObject.h"
#include "GameEngine/Input.h"
#include "GameEngine/Time.h"
#include "GameEngine/Rendering/SpriteSet.h"
#include "glm/gtc/random.hpp"
#include "glm/gtx/string_cast.hpp"

using namespace GameEngine;
using namespace GameEngine::Rendering;

SimpleWalker::SimpleWalker():
    Component("Simple Walker") {}

void SimpleWalker::OnStart()
{
    _characterController = _gameObject->GetComponent<GameEngine::Components::CharacterController>();
    _audioSource         = _gameObject->GetComponent<GameEngine::Components::AudioSource>();
    _spriteRenderer      = _gameObject->GetComponent<GameEngine::Components::SpriteRenderer>();

    _walkLeftSprite  = GET_SPRITE(GamerDudeWalkLeft);
    _walkRightSprite = GET_SPRITE(GamerDudeWalkRight);

    _scale          = _transform->GetLocalScale().x;
    _moveSpeed      = _moveSpeed / _scale;
    _animationSpeed = 10.0f / _scale;

    RandomizeMoveTimers();
    RandomizeSoundTimer();
}

void SimpleWalker::RandomizeMoveTimers()
{
    _canMoveTimer = glm::linearRand(0.70f * _scale, 1.0f * _scale);
    _moveTimer    = glm::linearRand(0.40f * _scale, 0.8f * _scale);
}

void SimpleWalker::RandomizeSoundTimer() { _soundTimer = glm::linearRand(3.0f * _scale, 4.0f * _scale); }

void SimpleWalker::OnUpdate()
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
            const glm::vec3 walkDir = glm::vec3(_randomDirection.x, 0, _randomDirection.y);
            const glm::quat lookDir = glm::quatLookAt(walkDir, _transform->GetUp());
            _characterController->Move((glm::vec2(_randomDirection.x, _randomDirection.y) * _moveSpeed));
            _transform->SetRotation(glm::slerp(_transform->GetRotation(), lookDir, 0.125f / _scale));
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
