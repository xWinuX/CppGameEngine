#include "GameEngine/Rendering/FrameBuffer.h"

using namespace GameEngine::Rendering;

struct Vertex
{
    glm::vec2 Position;
    glm::vec2 UV;
};

FrameBuffer::FrameBuffer(glm::uvec2 size, const GLbitfield clearBits):
    _clearBits(clearBits)
{
    glGenFramebuffers(1, &_frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &_frameBufferID);
}

void FrameBuffer::AttachTexture(const Texture2D* texture, const GLenum attachment)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->GetTextureID(), 0);
}

void FrameBuffer::AttachTexture(const Texture2DArray* texture, const GLenum attachment)
{
    glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture->GetTextureID(), 0);
}

void FrameBuffer::AttachRenderBuffer(const RenderBuffer* renderBuffer, const GLenum attachment)
{
    renderBuffer->Bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderBuffer->GetRenderBufferId());
    renderBuffer->Unbind();
}

void FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);
}

void FrameBuffer::Clear() const
{
    glClear(_clearBits);
}

void FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
