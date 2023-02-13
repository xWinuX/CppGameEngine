#pragma once

#include "GameEngine/Rendering/Shader.h"

namespace GameEngine
{
    namespace Rendering
    {
        class ShaderUseCallback
        {
            public:
                virtual void OnShaderUse(Shader* shader) {}
        };
    }
}
