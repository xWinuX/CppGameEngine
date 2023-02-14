#pragma once
#include "Component.h"
#include "fmod_common.h"
#include "glm/vec3.hpp"
#include "glm/gtc/constants.hpp"

namespace GameEngine
{
    namespace Components
    {
        class AudioListener final : public Component
        {
            public:
                AudioListener();
                void OnUpdateEnd() override;

            private:
                FMOD_VECTOR _fmodPosition = {0, 0, 0};
                FMOD_VECTOR _fmodUp       = {0, 1, 0};
                FMOD_VECTOR _fmodForward  = {0, 0, 1};
        };
    }
}
