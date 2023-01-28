#pragma once
#include "Component.h"
#include "../Rendering/Shader.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderer;
    }
    
    namespace Components
    {
        class Light : public Component
        {
            friend Rendering::Renderer;
            
            protected:
                GameEngine::Rendering::Shader* _shader;

                void OnUpdateEnd() override;
                virtual void OnShaderUse() = 0;
                virtual void OnFrameEnd() = 0;
            public:
                explicit     Light(GameEngine::Rendering::Shader* shader);

        };
    }
}
