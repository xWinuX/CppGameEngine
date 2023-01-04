#pragma once
#include "Component.h"
#include "../Rendering/Shader.h"


namespace GameEngine
{
    namespace Components
    {
        class Light : public Component
        {
            protected:
            GameEngine::Rendering::Shader* _shader;
            public:
            explicit Light(GameEngine::Rendering::Shader* shader);
            void OnBeforeRender() override;
            virtual void OnShaderUse() = 0;
            virtual void OnFrameEnd() = 0;
        };
    }
}