#include "GameEngine/Rendering/FrameBuffer.h"

#include "GameEngine/Window.h"

using namespace GameEngine::Rendering;

FrameBuffer::FrameBuffer(Shader* shader):
    _shader(shader)
{
        const glm::uvec2 currentWindowSize = Window::GetCurrentWindow()->GetSize();

    glGenFramebuffers(1, &_frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);

    // Bind Color Texture
    Texture::ImportSettings importSettings;
    importSettings.FilterMode     = Texture::Nearest;
    importSettings.WrapMode       = Texture::ClampToEdge;
    importSettings.InternalFormat = GL_RGB;
    importSettings.Format         = GL_RGB;
    _framebufferTexture           = new Texture(nullptr, currentWindowSize, importSettings);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _framebufferTexture->GetTextureID(), 0);

    // Create render buffer
    glGenRenderbuffers(1, &_renderBufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, static_cast<GLsizei>(currentWindowSize.x), static_cast<GLsizei>(currentWindowSize.y));
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBufferID);

    struct Vertex
    {
        glm::vec2 Position;
        glm::vec2 UV;
    };
    const Vertex vertices[] = {
            {{-1, -1}, {0, 0}}, // Top Left
            {{1, -1}, {1, 0}},  // Top Right
            {{-1, 1}, {0, 1}},  // Bottom Left
            {{1, 1}, {1, 1}},   // Bottom Right
        };

    const unsigned int indices[] = {
        0, 1, 2,
        1, 3, 2
    };

    VertexBufferAttribute* vertexAttributes = new VertexBufferAttribute[2]
    {
        VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr),
        VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(sizeof(glm::vec2)))
    };

    _vertexArrayObject = new VertexArrayObject(
                                               new VertexBuffer(reinterpret_cast<const unsigned char*>(vertices), sizeof(Vertex), 4),
                                               new IndexBuffer(reinterpret_cast<const unsigned char*>(indices), sizeof(unsigned int), 6),
                                               new VertexBufferLayout(vertexAttributes, 2)
                                              );
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &_frameBufferID);
    glDeleteRenderbuffers(1, &_renderBufferID);
    delete _framebufferTexture;
}

void FrameBuffer::Draw() const
{
    _shader->Use();
    _vertexArrayObject->Bind();
    _framebufferTexture->Bind(0);
    _vertexArrayObject->Render();
    _vertexArrayObject->Unbind();
}

void FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);
}

void FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
