﻿#pragma once
#include <map>
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
            public:
                struct CharacterInfo
                {
                    Sprite*                   Sprite;
                    msdf_atlas::GlyphGeometry GlyphGeometry;
                };

                explicit                        Font(const std::string& ttsFilePath);
                SpriteSet*                      GetSprite() const;
                Texture*                        GetTexture() const;
                const CharacterInfo*            GetCharacterInfo(msdfgen::unicode_t character);
                const msdf_atlas::FontGeometry& GetFontGeometry();
                float                           GetScale() const;
            private:
                Texture*                                    _texture;
                SpriteSet*                                  _sprite;
                msdf_atlas::FontGeometry                    _fontGeometry;
                float                                       _scale;
                std::map<msdfgen::unicode_t, CharacterInfo> _characterToSpriteFrameIndexMap;
        };
    }
}