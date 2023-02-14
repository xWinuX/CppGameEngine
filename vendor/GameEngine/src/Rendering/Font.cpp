#include "GameEngine/Rendering/Font.h"

#include <stb_image_write.h>
#include <msdf-atlas-gen/msdf-atlas-gen.h>
#include <tiny_gltf.h>

using namespace msdf_atlas;
using namespace GameEngine::Rendering;

Font::Font(const std::string& ttsFilePath)
{
    if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype())
    {
        if (msdfgen::FontHandle* font = msdfgen::loadFont(ft, ttsFilePath.c_str()))
        {
            std::vector<GlyphGeometry> glyphs;

            FontGeometry fontGeometry(&glyphs);

            fontGeometry.loadCharset(font, 1.0, Charset::ASCII);
            for (GlyphGeometry& glyph : glyphs) { glyph.edgeColoring(&msdfgen::edgeColoringInkTrap, 3.0, 0); }
            TightAtlasPacker packer;
            packer.setDimensionsConstraint(TightAtlasPacker::DimensionsConstraint::POWER_OF_TWO_SQUARE);
            packer.setMinimumScale(36.0);
            packer.setPixelRange(2.0);
            packer.setMiterLimit(3.0);
            packer.setPadding(3);
            packer.pack(glyphs.data(), glyphs.size());

            int width = 0, height = 0;
            packer.getDimensions(width, height);

            ImmediateAtlasGenerator<float, 3, &msdfGenerator, BitmapAtlasStorage<byte, 3>> generator(width, height);
            GeneratorAttributes                                                            attributes;

            generator.setAttributes(attributes);
            generator.setThreadCount(4);
            generator.generate(glyphs.data(), glyphs.size());

            const msdfgen::BitmapConstRef<byte, 3> atlasStorage = generator.atlasStorage();

            TextureParams textureParams;
            textureParams.Format         = GL_RGB;
            textureParams.InternalFormat = GL_RGB8;
            _texture                     = new Texture2D(const_cast<unsigned char*>(atlasStorage.pixels), glm::uvec2(atlasStorage.width, atlasStorage.height), textureParams);
            _sprite                      = new SpriteSet(_texture, fontGeometry);

            _fontGeometry = fontGeometry;
            _scale        = 1.0f / static_cast<float>(_fontGeometry.getMetrics().ascenderY - _fontGeometry.getMetrics().descenderY);

            size_t spriteFrameIndex = 0;
            for (const GlyphGeometry& glyphGeometry : glyphs)
            {
                _characterToSpriteFrameIndexMap[glyphGeometry.getCodepoint()] = CharacterInfo{_sprite->GetSprite(spriteFrameIndex), glyphGeometry};
                spriteFrameIndex++;
            }

            // Cleanup
            msdfgen::destroyFont(font);
        }
        msdfgen::deinitializeFreetype(ft);
    }
}

SpriteSet* Font::GetSprite() const { return _sprite; }
Texture2D* Font::GetTexture() const { return _texture; }

const Font::CharacterInfo* Font::GetCharacterInfo(const msdfgen::unicode_t character)
{
    const auto found = _characterToSpriteFrameIndexMap.find(character);
    if (found == _characterToSpriteFrameIndexMap.end()) { return nullptr; }
    return &(found->second);
}

const msdf_atlas::FontGeometry& Font::GetFontGeometry() { return _fontGeometry; }
float                           Font::GetScale() const { return _scale; }
