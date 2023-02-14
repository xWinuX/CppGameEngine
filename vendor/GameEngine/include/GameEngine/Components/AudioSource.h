#pragma once
#include "Component.h"
#include "GameEngine/Audio/Sound.h"


namespace GameEngine
{
    namespace Components
    {
        class AudioSource final : public Component
        {
            private:
                Audio::Sound*  _sound;
                FMOD::Channel* _fmodChannel      = nullptr;
                FMOD_VECTOR    _fmodPosition     = FMOD_VECTOR{0, 0, 0};
                bool           _startImmediately = false;
                bool           _startWithLoop    = false;
                float          _volume           = 1.0f;

            public:
                explicit AudioSource(Audio::Sound* sound, const bool startImmediately, const bool loop);
                AudioSource(Audio::Sound* sound);

                void OnStart() override;
                void OnUpdateEnd() override;
                void OnGuiDraw() override;

                void SetVolume(const float volume);
                void Pause();
                void Continue();
                void Play();
                void PlayPitch(const float pitch);
                void PlayLooped();
        };
    }
}
