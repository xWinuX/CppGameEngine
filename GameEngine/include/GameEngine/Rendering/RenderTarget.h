#pragma once
#include "FrameBuffer.h"
#include "Primitive.h"
#include "RenderBuffer.h"
#include "ShaderUseCallback.h"
#include "GameEngine/Layer.h"

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

                bool GetRenderShadows() const;
                void SetRenderShadows(bool renderShadows);
            
                // Layer Mask Source: https://dietertack.medium.com/using-bit-flags-in-c-d39ec6e30f08#:~:text=Bit%20flags%20are%20a%20programming,bit%20to%20represent%20each%20state.
                void AddActiveLayer(Layer layer);
                void RemoveActiveLayer(Layer layer);
                bool HasActiveLayer(Layer layer) const;
            protected:
                void         ResizeFrameBuffer(glm::uvec2 size);
                virtual void Bind();
                virtual void Unbind() const;
                virtual void Draw();

            private:
                uint8_t _layerMask = 1;
            
                TextureParams _renderTextureParams;

                FrameBuffer*  _frameBuffer   = nullptr;
                RenderBuffer* _renderBuffer  = nullptr;
                Texture2D*      _renderTexture = nullptr;

                Shader*               _shader;
                Rendering::Primitive* _screenQuad;

                bool _renderShadows = true;

                void CreateRenderingSetup(const glm::uvec2 size);
        };
    }
}
