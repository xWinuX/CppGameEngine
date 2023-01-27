#include "GameEngine/Audio/Sound.h"

#include "GameEngine/Application.h"
#include "GameEngine/Audio/AudioManager.h"
#include "GameEngine/Debug/Log.h"


using namespace GameEngine::Audio;
using namespace GameEngine::Debug;

Sound::Sound(const std::string& filePath)
{
    FMOD_CALLS_BEGIN
    FMOD_CALL(AudioManager::GetFMODSystem()->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &_fmodSound), "Failed to create sound")
}

FMOD::Sound* Sound::GetFMODSound() const { return _fmodSound; }
