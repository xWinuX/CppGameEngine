#include "GameEngine/Components/TextRenderer.h"

#include "GameEngine/GameObject.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Rendering;
using namespace GameEngine::Components;

void TextRenderer::UpdateQuads()
{
    // Clear quads and resize to fit text
    _quads.clear();
    if (_quads.capacity() < _text.size()) { _quads.reserve(_text.size()); }

    glm::vec2   cursor     = glm::zero<glm::vec2>();
    size_t      offset     = 0;
    glm::mat4   trs        = _transform->GetTRS();
    const float lineHeight = static_cast<float>(_font->GetFontGeometry().getMetrics().lineHeight) * _font->GetScale();
    for (const char c : _text)
    {
        // Ignore carriage return
        if (c == '\r') { continue; }

        // If new line reset cursor.x and add line height to cursor.y
        if (c == '\n')
        {
            cursor.x = 0;
            cursor.y -= lineHeight;
            continue;
        }

        const Font::CharacterInfo* characterInfo = _font->GetCharacterInfo(c);

        if (characterInfo == nullptr) { continue; }

        if (!characterInfo->GlyphGeometry.isWhitespace())
        {
            const Sprite* sprite = characterInfo->Sprite;

            Sprite::QuadData* quadData = sprite->GetQuadDataPtr();
            quadData->Transform[3][0]  = trs[3][0] + cursor.x;
            quadData->Transform[3][1]  = trs[3][1] + cursor.y;

            _quads.emplace_back(*sprite->GetQuadDataPtr());
            offset += GetQuadSize();
        }

        cursor.x += static_cast<float>(characterInfo->GlyphGeometry.getAdvance()) * _font->GetScale();
    }
}

TextRenderer::TextRenderer(Rendering::Font* font, Rendering::Material* material):
    _font(font),
    _material(material) { }

void TextRenderer::OnStart() { UpdateQuads(); }

void TextRenderer::OnUpdateEnd()
{
    // Update quads needed
    if (_needsUpdate) { UpdateQuads(); }

    SetLayer(_gameObject->GetLayer());
    Renderer::SubmitBatchRenderable2D(this);
}

Material* TextRenderer::GetMaterial() { return _material; }
Texture*  TextRenderer::GetTexture() { return _font->GetTexture(); }
size_t    TextRenderer::GetQuadSize() { return sizeof(Sprite::QuadData); }
size_t    TextRenderer::GetCopySize() { return _quads.size() * GetQuadSize(); }

void TextRenderer::CopyQuadData(unsigned char* destination) { memcpy(destination, _quads.data(), _quads.size() * GetQuadSize()); }

void TextRenderer::SetText(const std::string& text)
{
    _text        = text;
    _needsUpdate = true;
}
