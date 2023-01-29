﻿#include "GameEngine/Components/AudioSource.h"

#include <glm/gtx/string_cast.hpp>

#include "GameEngine/Audio/AudioManager.h"
#include "GameEngine/Debug/Log.h"

using namespace GameEngine::Components;
using namespace GameEngine::Audio;

#define FMOD_CHANNEL_NULL_CHECK_CALL(call, message) \
    if (_fmodChannel == nullptr) { Debug::Log::Error("FMOD Channel is null"); } \
    FMOD_CHANNEL_CALL(##call##, ##message##)

#define FMOD_CHANNEL_CALL(call, message) FMOD_SINGLE_CALL(##call##, ##message##, _fmodChannel = nullptr;)

AudioSource::AudioSource(Sound* sound):
    AudioSource(sound, false) { }

AudioSource::AudioSource(Audio::Sound* sound, const bool startImmediately):
    _sound(sound),
    _startImmediately(startImmediately) {}

void AudioSource::OnStart() { if (_startImmediately) { Play(); } }
void AudioSource::OnUpdate() { }

void AudioSource::OnUpdateEnd()
{
    if (!_sound->Is3D()) { return; }

    if (_fmodChannel == nullptr) { return; }

    const glm::vec3 position = _transform->GetPosition();
    _fmodPosition            = FMOD_VECTOR{position.x, position.y, position.z};

    FMOD_CHANNEL_CALL(_fmodChannel->set3DAttributes(&_fmodPosition, nullptr))
}

void AudioSource::Pause() { FMOD_CHANNEL_NULL_CHECK_CALL(_fmodChannel->setPaused(true), "Failed to pause channel") }

void AudioSource::Continue() { FMOD_CHANNEL_NULL_CHECK_CALL(_fmodChannel->setPaused(false), "Failed to unpause channel") }

void AudioSource::Play() { FMOD_SINGLE_CALL(AudioManager::GetFMODSystem()->playSound(_sound->GetFMODSound(), nullptr, false, &_fmodChannel)) }

void AudioSource::PlayLooped() { Play(); }