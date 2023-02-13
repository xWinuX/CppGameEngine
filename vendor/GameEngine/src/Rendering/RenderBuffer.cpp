#include "GameEngine/Rendering/RenderBuffer.h"

#include "glad/glad.h"

RenderBuffer::RenderBuffer(const glm::uvec2 size, const GLenum format)
{
    glGenRenderbuffers(1, &_renderBufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, format, static_cast<GLsizei>(size.x), static_cast<GLsizei>(size.y));
}

RenderBuffer::~RenderBuffer()
{
    glDeleteRenderbuffers(1, &_renderBufferID);
}

void RenderBuffer::Bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBufferID);
}

void RenderBuffer::Unbind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

GLuint RenderBuffer::GetRenderBufferId() const { return _renderBufferID; }
