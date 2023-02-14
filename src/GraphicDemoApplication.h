#pragma once
#include "GameEngine/Application.h"

class GraphicDemoApplication final : public GameEngine::Application
{
    public:
        void Initialize(GameEngine::Scene& scene) override;

    private:
        void LoadTextures() const;
        void LoadSprites() const;
        void LoadFonts() const;
        void LoadSounds() const;
        void LoadModels() const;
        void LoadShaders() const;
        void LoadMaterials() const;
        void LoadAssets() const;
};
