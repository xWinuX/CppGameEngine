#pragma once
#include <string>

#include "fmod_studio.hpp"

namespace GameEngine
{
    namespace Audio
    {
        class Sound
        {
            private:
                FMOD::Sound* _fmodSound = nullptr;

            public:
                explicit Sound(const std::string& filePath);
                FMOD::Sound* GetFMODSound() const;
        };
    }
}
