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
                FMOD::Channel* _fmodChannel  = nullptr;
                FMOD_VECTOR    _fmodPosition = FMOD_VECTOR{0, 0, 0};
                bool           _startImmediately;

            public:
                explicit AudioSource(Audio::Sound* sound);
                explicit AudioSource(Audio::Sound* sound, bool startImmediately);

                void OnStart() override;
                void OnUpdate() override;
                void OnUpdateEnd() override;

                void Pause();
                void Continue();
                void Play();
                void PlayLooped();
        };
    }
}
