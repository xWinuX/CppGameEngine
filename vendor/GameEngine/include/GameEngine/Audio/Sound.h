#pragma once
#include <fmod_studio.hpp>
#include <string>

namespace GameEngine
{
    namespace Audio
    {
        class Sound
        {
            public:
                explicit     Sound(const std::string& filePath);
                explicit     Sound(const std::string& filePath, const bool is3D = false);
                FMOD::Sound* GetFMODSound() const;
                bool         Is3D() const;

            private:
                FMOD::Sound* _fmodSound = nullptr;
                bool         _is3D;
        };
    }
}
