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
                bool         _is3D;

            public:
                explicit     Sound(const std::string& filePath);
                explicit     Sound(const std::string& filePath, const bool is3D = false);
                FMOD::Sound* GetFMODSound() const;
                bool         Is3D() const;
        };
    }
}
