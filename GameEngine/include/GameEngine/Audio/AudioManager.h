#pragma once
#include <fmod.hpp>

#include "GameEngine/Application.h"

#define FMOD_CALLS_BEGIN FMOD_RESULT result;
#define FMOD_CALL(call, message) \
result = call; \
if (result != FMOD_OK) { Debug::Log::Error(std::string(##message##) + " " + std::to_string(result)); }

namespace GameEngine
{
    namespace Audio
    {
        class AudioManager
        {
            friend Application;

            public:
                static FMOD::System* GetFMODSystem();

            private:
                static FMOD::System* _fmodSystem;
                static void          Initialize();
        };
    }
}
