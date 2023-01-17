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
                struct PackingSprite
                {
                    Sprite*      Sprite;
                    unsigned int PackedFrames;
                    bool         WasPacked;
                    std::vector<unsigned int> FramePages;
                };

                std::vector<PackingSprite>  _sprites;
                std::vector<Texture*>       _pages;
                std::vector<unsigned char*> _buffers;
                glm::uvec2                  _size;
                glm::uvec2                  _currentPosition = glm::zero<glm::uvec2>();
                glm::vec2                   _uvStep;
            public:
                explicit SpriteAtlas(glm::uvec2 size);
                void     ExportPages() const;
                void     AddSprite(Sprite* sprite);
                void     CreateNewPage();
                void     Pack();
        };
    }
}
