#pragma once
#include "GameEngine/Components/AudioSource.h"
#include "GameEngine/Components/CharacterController.h"
#include "GameEngine/Components/Component.h"
#include "GameEngine/Components/SpriteRenderer.h"
#include "glm/gtc/random.hpp"

class SimpleWalker final : public GameEngine::Components::Component
{
    private:
        GameEngine::Components::AudioSource*         _audioSource         = nullptr;
        GameEngine::Components::SpriteRenderer*      _spriteRenderer      = nullptr;
        GameEngine::Components::CharacterController* _characterController = nullptr;
        GameEngine::Rendering::SpriteSet*            _walkRightSprite     = nullptr;
        GameEngine::Rendering::SpriteSet*            _walkLeftSprite      = nullptr;

        float _soundTimer     = 1;
        float _canMoveTimer   = 1;
        float _animationSpeed = 0;
        float _moveTimer      = 2;
        float _moveSpeed      = 1000;
        bool  _canMove        = false;
        float _scale          = 1;

        glm::vec2 _randomDirection = glm::circularRand(1);

    public:
        SimpleWalker();
        void OnStart() override;
        void RandomizeMoveTimers();
        void RandomizeSoundTimer();
        void OnUpdate() override;
};
