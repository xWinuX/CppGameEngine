#include "GameEngine/Audio/Sound.h"

#include "GameEngine/Application.h"
#include "GameEngine/Audio/AudioManager.h"
#include "GameEngine/Debug/Log.h"

using namespace GameEngine::Audio;
using namespace GameEngine::Debug;

Sound::Sound(const std::string& filePath):
    Sound(filePath, FMOD_DEFAULT) {}

Sound::Sound(const std::string& filePath, const bool is3D):
    _is3D(is3D)
{
    const FMOD_MODE mode = is3D ? FMOD_3D : FMOD_DEFAULT;
    FMOD_CALLS_BEGIN
    FMOD_CALL(AudioManager::GetFMODSystem()->createSound(filePath.c_str(), mode, 0, &_fmodSound), "Failed to create sound")
}

FMOD::Sound* Sound::GetFMODSound() const { return _fmodSound; }
bool         Sound::Is3D() const { return _is3D; }
