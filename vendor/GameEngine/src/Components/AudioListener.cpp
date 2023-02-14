#include "GameEngine/Components/AudioListener.h"

#include "GameEngine/Audio/AudioManager.h"
#include "GameEngine/Debug/Log.h"

GameEngine::Components::AudioListener::AudioListener():
    Component("Audio Listener") {}

void GameEngine::Components::AudioListener::OnUpdateEnd()
{
    const glm::vec3 position = _transform->GetPosition();
    _fmodPosition            = FMOD_VECTOR{position.x, position.y, position.z};

    const glm::vec3 up = _transform->GetUp();
    _fmodUp            = FMOD_VECTOR{up.x, up.y, up.z};

    const glm::vec3 forward = _transform->GetForward();
    _fmodForward            = FMOD_VECTOR{forward.x, forward.y, forward.z};

    FMOD_CALLS_BEGIN
    FMOD_CALL(Audio::AudioManager::GetFMODSystem()->set3DListenerAttributes(0, &_fmodPosition, nullptr, &_fmodForward, &_fmodUp), "Couldn't set listener 3D Attributes")
}
