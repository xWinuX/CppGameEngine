#pragma once
#include <string>

#include "Texture.h"
#include "SpriteSet.h"

namespace GameEngine
{
    namespace Rendering
    {
        class SpriteSet;

        class Font
        {
            private:
                Texture* _texture;
                SpriteSet*  _sprite;
            public:
                explicit Font(const std::string& ttsFilePath);
                SpriteSet* GetSprite() const;
        };
    }
}
