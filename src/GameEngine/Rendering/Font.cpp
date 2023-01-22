#include "Font.h"
#include <msdf-atlas-gen/msdf-atlas-gen.h>

#include "stb_image_write.h"
#include "tiny_gltf.h"

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

            fontGeometry.loadCharset(font, 2.0, Charset::ASCII);
            for (GlyphGeometry& glyph : glyphs) { glyph.edgeColoring(&msdfgen::edgeColoringInkTrap, 3.0, 0); }
            TightAtlasPacker packer;
            packer.setDimensionsConstraint(TightAtlasPacker::DimensionsConstraint::POWER_OF_TWO_SQUARE);
            packer.setMinimumScale(24.0);
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

            Texture::ImportSettings importSettings;
            importSettings.Format = GL_RGB; 
            importSettings.InternalFormat = GL_RGB8; 
            _texture = new Texture(const_cast<unsigned char*>(atlasStorage.pixels), glm::uvec2(atlasStorage.width, atlasStorage.height), importSettings);
            _sprite  = new SpriteSet(_texture, glyphs);
            
            stbi_write_png("FontAtlas.png", atlasStorage.width, atlasStorage.height, 3, atlasStorage.pixels, width * 3);

            // Cleanup
            msdfgen::destroyFont(font);
        }
        msdfgen::deinitializeFreetype(ft);
    }
}

SpriteSet* Font::GetSprite() const { return _sprite; }
