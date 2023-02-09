#pragma once
#include "FrameBuffer.h"
#include "RenderBuffer.h"
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
                virtual  ~RenderTarget();

            protected:
                void         ResizeFrameBuffer(glm::uvec2 size);
                virtual void Bind();
                virtual void Unbind() const;

            private:
                Texture::ImportSettings _renderTextureImportSettings;

                FrameBuffer*  _frameBuffer   = nullptr;
                RenderBuffer* _renderBuffer  = nullptr;
                Texture*      _renderTexture = nullptr;

                Shader*               _shader;
                Rendering::Primitive* _screenQuad;

                void CreateRenderingSetup(const glm::uvec2 size);
        };
    }
}
