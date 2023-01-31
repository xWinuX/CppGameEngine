#pragma once
#include "FrameBuffer.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderer;

        class RenderTarget
        {
            friend Renderer;

            public:
                explicit RenderTarget(Shader* shader);

            protected:
                void ResizeFrameBuffer(glm::uvec2 newSize);

            private:
                FrameBuffer* _frameBuffer;
                Shader*      _shader;

                virtual void OnShaderUse(Shader* shader) {}
                void         Bind() const;
                void         Unbind() const;
        };
    }
}
