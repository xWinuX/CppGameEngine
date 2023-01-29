#pragma once
#include "Component.h"
#include "../Rendering/Font.h"
#include "../Rendering/Material.h"
#include "../Rendering/Renderable2D.h"
#include "../Rendering/Sprite.h"

namespace GameEngine
{
    namespace Components
    {
        class TextRenderer final : public Component, public Rendering::Renderable2D
        {
            private:
                Rendering::Font*                         _font;
                Rendering::Material*                     _material;
                std::string                              _text        = "abcdefghij\nklmnopqrstuvxy";
                std::vector<Rendering::Sprite::QuadData> _quads       = std::vector<Rendering::Sprite::QuadData>(32);
                bool                                     _needsUpdate = false;
                void                                     UpdateQuads();

            protected:
                void OnStart() override;
                void OnUpdateEnd() override;

            public:
                TextRenderer(Rendering::Font* font, Rendering::Material* material);

                Rendering::Material* GetMaterial() override;
                Rendering::Texture*  GetTexture() override;
                size_t               GetQuadSize() override;
                size_t               GetCopySize() override;
                void                 CopyQuadData(unsigned char* destination) override;
                void                 SetText(const std::string& text);
        };
    }
}
