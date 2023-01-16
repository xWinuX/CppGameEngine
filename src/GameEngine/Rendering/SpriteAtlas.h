#pragma once
#include <glm/vec2.hpp>

#include "Sprite.h"
#include "glm/gtc/constants.hpp"


namespace GameEngine
{
    namespace Rendering
    {
        class SpriteAtlas
        {
            private:
                unsigned char* _buffer;
                glm::uvec2 _size;
                glm::uvec2 _currentPosition = glm::zero<glm::uvec2>();
            public:
                explicit SpriteAtlas(glm::uvec2 size);
                void     ExportImage() const;
                void     AddSprite(const Sprite* sprite) ;
        };
    }
}

