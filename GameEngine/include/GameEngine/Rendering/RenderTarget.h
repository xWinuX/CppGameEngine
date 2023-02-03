#pragma once
#include "FrameBuffer.h"
#include "ShaderUseCallback.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Renderer;

        class RenderTarget : public ShaderUseCallback
        {
            friend Renderer;

            public:
                explicit RenderTarget(Shader* shader);

            protected:
                void ResizeFrameBuffer(glm::uvec2 newSize);

            private:
                FrameBuffer* _frameBuffer;
                Shader*      _shader;

                void         Bind() const;
                void         Unbind() const;
        };
    }
}
