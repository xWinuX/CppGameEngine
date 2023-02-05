#pragma once
#include "GameEngine/Application.h"

class GraphicDemoApplication final : public GameEngine::Application
{
    private:
        void LoadTextures();
        void LoadSprites();
        void LoadFonts() const;
        void LoadSounds() const;
        void LoadModels() const;
        void LoadShaders() const;
        void LoadMaterials() const;
        void LoadAssets();
    public:
        void Initialize(GameEngine::Scene& scene) override;
};
