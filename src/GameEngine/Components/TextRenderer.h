#pragma once
#include "Component.h"
#include "../Rendering/Font.h"
#include "../Rendering/Material.h"
#include "../Rendering/Renderable2D.h"

namespace GameEngine
{
    namespace Components
    {
        class TextRenderer final : public Component, public Rendering::Renderable2D
        {
            private:
                Rendering::Font*     _font;
                Rendering::Material* _material;
                std::string          _text = "()abc-.";

            public:
                TextRenderer(Rendering::Font* font, Rendering::Material* material);

                void                 OnBeforeRender() override;
                Rendering::Material* GetMaterial() override;
                Rendering::Texture*  GetTexture() override;
                size_t               GetQuadSize() override;
                size_t               GetCopySize() override;
                void                 CopyQuadData(unsigned char* destination) override;
        };
    }
}
