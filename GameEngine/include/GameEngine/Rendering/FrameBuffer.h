#pragma once
#include "RenderBuffer.h"
#include "Texture2D.h"
#include "glad/glad.h"

namespace GameEngine
{
    namespace Rendering
    {
        class FrameBuffer
        {
            private:
                GLuint     _frameBufferID = 0;
                GLbitfield _clearBits;

            public:
                explicit FrameBuffer(glm::uvec2 size, GLbitfield clearBits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
                ~FrameBuffer();
                void AttachTexture(const Texture2D* texture, const GLenum attachment);
                void AttachRenderBuffer(const RenderBuffer* renderBuffer, const GLenum attachment);
                void Bind() const;
                void Clear() const;
                void Unbind();
        };
    }
}
