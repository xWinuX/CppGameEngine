#pragma once

#include "Buffers/UniformBuffer.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Material
        {
            private:
            Shader*        _shader;
            UniformBuffer* _uniformBuffer;

            public:
            explicit Material(Shader* shader);
            ~Material();
            Shader*        GetShader() const;
            UniformBuffer* GetUniformBuffer() const;
        };
    }
}
