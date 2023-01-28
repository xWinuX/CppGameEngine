#pragma once
#include "fmod.hpp"
#include "fmod_common.h"
#include "fmod_errors.h"
#include "GameEngine/Debug/Log.h"

#include "GameEngine/Application.h"

#define FMOD_CALLS_BEGIN FMOD_RESULT result;
#define FMOD_SINGLE_CALL(call, message, onError) FMOD_CALLS_BEGIN FMOD_CALL(##call##, ##message##, ##onError##)
#define FMOD_CALL(call, message, onError) result = call; FMOD_ERROR_CHECK(result, ##message##, ##onError##)
#define FMOD_ERROR_CHECK(result, message, onError) if (##result## != FMOD_OK) { Debug::Log::Error(std::string(##message##) + ": " + FMOD_ErrorString(result)); onError }

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
                static void          Update();
        };
    }
}
