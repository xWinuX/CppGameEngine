#pragma once
#include "GameEngine/Components/Component.h"
#include "GameEngine/Components/Rigidbody.h"
#include "glm/vec2.hpp"
#include "glm/gtc/constants.hpp"

namespace GameEngine
{
    namespace Components
    {
        class CharacterController : public GameEngine::Components::Component
        {
            private:
                GameEngine::Components::Rigidbody* _rigidbody     = nullptr;
                glm::vec2                          _moveDirection = glm::zero<glm::vec3>();
                float                              _jumpStrength  = 0.0f;

            protected:
                void OnStart() override;
                void OnPhysicsUpdate() override;

            public:
                CharacterController();
                void Move(glm::vec2 direction);
                void Move(glm::vec2 direction, const Transform* transform);
                void Jump(float strength);
        };
    }
}
