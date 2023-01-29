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

                void OnUpdateEnd() override;
                virtual void OnShaderUse(Rendering::Shader* shader) = 0;
                virtual void OnFrameEnd() = 0;
        };
    }
}
