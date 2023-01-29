#pragma once
#include "GameEngine/Components/AudioSource.h"
#include "GameEngine/Components/Component.h"
#include "GameEngine/Components/SpriteRenderer.h"
#include "glm/gtc/random.hpp"

class CarstenBehaviour final : public GameEngine::Components::Component
{
    private:
        GameEngine::Components::AudioSource* _audioSource = nullptr;
        GameEngine::Components::SpriteRenderer* _spriteRenderer = nullptr;
    
        float _canMoveTimer = 1;
        float _moveTimer = 2;
        float _moveSpeed = 2;
        bool _canMove = false;

        glm::vec2 _randomDirection = glm::circularRand(1);
    public:
        void OnStart() override;
        void OnUpdate() override;
        
};
