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
size_t    TextRenderer::GetCopySize() { return _text.size() * GetQuadSize(); }

void TextRenderer::CopyQuadData(unsigned char* destination)
{
    size_t    offset = 0;
    glm::mat4 trs    = _transform->GetTRS();
    std::cout << "------------" << std::endl;

    for (const char c : _text)
    {
        std::cout << "begin" <<std::endl;
        const Font::CharacterInfo*       characterInfo = _font->GetCharacterInfo(c);

        
        
        if (characterInfo == nullptr) { continue; }

        Sprite* sprite = characterInfo->Sprite;

        const float scale = 1.0f / static_cast<float>(_font->GetFontMetrics().ascenderY - _font->GetFontMetrics().descenderY);
        
        Sprite::QuadData* quadData = sprite->GetQuadDataPtr();
        const float       factor   = sprite->GetPixelsPerUnitFactor() * static_cast<float>(sprite->GetSize().x);

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
        std::cout << "scale: " << scale << std::endl;

        quadData->Transform[3][0] = trs[3][0];
        quadData->Transform[3][1] = trs[3][1];

        memcpy(destination + offset, sprite->GetQuadData(), GetCopySize());
        const float advance = characterInfo->Advance;
        std::cout << "final advance: " << advance << std::endl;
        trs[3][0] += advance;
        offset += GetQuadSize();
    }
}
