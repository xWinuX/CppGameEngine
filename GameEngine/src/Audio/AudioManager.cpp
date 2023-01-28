#include "GameEngine/Audio/AudioManager.h"

#include "GameEngine/Debug/Log.h"

using namespace GameEngine::Audio;
using namespace GameEngine::Debug;

FMOD::System* AudioManager::_fmodSystem = nullptr;

void AudioManager::Initialize()
{
    FMOD_CALLS_BEGIN
    FMOD_CALL(FMOD::System_Create(&_fmodSystem), "Failed to create FMOD System")
    FMOD_CALL(_fmodSystem->init(128, FMOD_INIT_NORMAL, 0), "Failed to initialize fmod system")
}

void AudioManager::Update()
{
    _fmodSystem->update();
}

FMOD::System* AudioManager::GetFMODSystem() { return _fmodSystem; }
