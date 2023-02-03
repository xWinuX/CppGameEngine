#pragma once
#include "Component.h"
#include "GameEngine/Rendering/ShaderUseCallback.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderer;
    }
    
    namespace Components
    {
        class Light : public Component, public Rendering::ShaderUseCallback
        {
            friend Rendering::Renderer;
            private:
                static bool _alreadySubmitted = false;
            protected:
                void OnUpdateBegin() override;
                void OnUpdateEnd() override;
                virtual void OnFrameEnd() = 0;
        };
    }
}
