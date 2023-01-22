﻿#pragma once
#include <glm/vec2.hpp>

#include "SpriteSet.h"
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
                    Sprite* Sprite;
                    bool    WasPacked;
                    size_t  PageIndex;
                };


                std::vector<PackingSprite>  _sprites;
                std::vector<Texture*>       _pages;
                std::vector<unsigned char*> _buffers;

                Texture::ImportSettings _importSettings;
                glm::uvec2              _size;
                glm::uvec2              _currentPosition = glm::zero<glm::uvec2>();
                glm::vec2               _uvStep;

                void SortSpritesByHeight();

            public:
                explicit SpriteAtlas(glm::uvec2 size, Texture::ImportSettings importSettings);
                void     ExportPages() const;
                void     AddSprite(SpriteSet* spriteSet);
                void     AddSprite(Sprite* sprite);
                void     CreateNewPage();
                void     Pack();
        };
    }
}
