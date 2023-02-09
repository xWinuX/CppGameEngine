#pragma once
#include "RenderBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "GameEngine/Rendering/Primitives/ScreenQuad.h"
#include "glad/glad.h"

namespace GameEngine
{
    namespace Rendering
    {
        class FrameBuffer
        {
            private:
                GLuint _frameBufferID = 0;

            public:
                explicit FrameBuffer(glm::uvec2 size);
                ~FrameBuffer();
                void AttachTexture(const Texture* texture, const GLenum attachment);
                void BindRenderBuffer(const RenderBuffer* renderBuffer, const GLenum attachment);
                void Bind() const;
                void Unbind();
        };
    }
}
