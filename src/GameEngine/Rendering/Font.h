#pragma once
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
                    Sprite*                Sprite;
                    float                  Advance;
                    msdfgen::Shape::Bounds Bounds;
                    glm::vec2              Translation;
                };

                explicit                    Font(const std::string& ttsFilePath);
                SpriteSet*                  GetSprite() const;
                Texture*                    GetTexture() const;
                const CharacterInfo*        GetCharacterInfo(msdfgen::unicode_t character);
                const msdfgen::FontMetrics& GetFontMetrics() const;
                float                       GetGeometryScale() const;
                const msdf_atlas::FontGeometry& GetFontGeometry();

            private:
                Texture*                                    _texture;
                SpriteSet*                                  _sprite;
                float                                       _geometryScale;
                msdf_atlas::FontGeometry                    _fontGeometry;
                msdfgen::FontMetrics                        _fontMetrics;
                std::map<msdfgen::unicode_t, CharacterInfo> _characterToSpriteFrameIndexMap;
        };
    }
}
