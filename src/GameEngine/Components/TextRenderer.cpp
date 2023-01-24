#include "TextRenderer.h"

#include "Transform.h"
#include "../Rendering/Sprite.h"
#include "../Rendering/Renderer.h"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;

TextRenderer::TextRenderer(Rendering::Font* font, Rendering::Material* material):
    _font(font),
    _material(material) { }

void TextRenderer::OnBeforeRender() { Renderer::SubmitRenderable2D(this); }

Material* TextRenderer::GetMaterial() { return _material; }
Texture*  TextRenderer::GetTexture() { return _font->GetTexture(); }
size_t    TextRenderer::GetQuadSize() { return sizeof(Sprite::QuadData); }
size_t    TextRenderer::GetCopySize() { return _text.size() * GetQuadSize() * 10; }

void TextRenderer::CopyQuadData(unsigned char* destination)
{
    glm::vec2 cursor = glm::zero<glm::vec2>();
    size_t    offset = 0;
    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 trs = _transform->GetTRS();
        std::cout << "------------" << std::endl;

        for (const char c : _text)
        {
            // Ignore carriage return
            if (c == '\r') { continue; }

            // If new line reset cursor.x and add line height to cursor.y
            if (c == '\n')
            {
                cursor.x = 0;
                cursor.y -= static_cast<float>(_font->GetFontGeometry().getMetrics().lineHeight) * _font->GetScale();
                continue;
            }

            const Font::CharacterInfo* characterInfo = _font->GetCharacterInfo(c);

            // TODO: Maybe have a default character that gets displayed instead
            if (characterInfo == nullptr) { continue; }


            if (!characterInfo->GlyphGeometry.isWhitespace())
            {
                Sprite* sprite = characterInfo->Sprite;


                /*
                std::cout << "em: " << _font->GetFontMetrics().emSize << std::endl;
                std::cout << "scale: " << _font->GetGeometryScale() << std::endl;
                std::cout << "lineheight: " << _font->GetFontMetrics().lineHeight << std::endl;
                std::cout << "ascendery: " << _font->GetFontMetrics().ascenderY << std::endl;
                std::cout << "advance: " << characterInfo->Advance << std::endl;
                std::cout << "factor: " << factor << std::endl;
                std::cout << "boundtop: " << characterInfo->Bounds.t << std::endl;
                //std::cout << "boundtop2: " << pt << std::endl;
                std::cout << "boundbot: " << characterInfo->Bounds.b << std::endl;
                std::cout << "translationy: " << characterInfo->Translation.y << std::endl;
                std::cout << "scale: " << scale << std::endl;*/

                Sprite::QuadData* quadData = sprite->GetQuadDataPtr();
                quadData->Transform[3][0]  = trs[3][0] + cursor.x;
                quadData->Transform[3][1]  = trs[3][1] + cursor.y;

                memcpy(destination + offset, sprite->GetQuadData(), GetCopySize());
                offset += GetQuadSize();
            }
            cursor.x += static_cast<float>(characterInfo->GlyphGeometry.getAdvance()) * _font->GetScale();
        }
    }
}
