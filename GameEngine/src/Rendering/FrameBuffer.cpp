#include "GameEngine/Rendering/FrameBuffer.h"


using namespace GameEngine::Rendering;

struct Vertex
{
    glm::vec2 Position;
    glm::vec2 UV;
};

FrameBuffer::FrameBuffer(glm::uvec2 size)
{
    glGenFramebuffers(1, &_frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);

    // Bind Color Texture
    Texture::ImportSettings importSettings;
    importSettings.FilterMode      = Texture::Nearest;
    importSettings.WrapMode        = Texture::ClampToEdge;
    importSettings.InternalFormat  = GL_RGB32F;
    importSettings.Format          = GL_RGB;
    importSettings.ChannelDataType = GL_FLOAT;
    _framebufferTexture            = new Texture(nullptr, size, importSettings);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _framebufferTexture->GetTextureID(), 0);

    // Create render buffer
    glGenRenderbuffers(1, &_renderBufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, static_cast<GLsizei>(size.x), static_cast<GLsizei>(size.y));
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBufferID);

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
        VertexBufferAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, UV)))
    };

    _primitive = new Primitive(
                               new VertexBuffer(reinterpret_cast<const unsigned char*>(vertices), sizeof(Vertex), 4),
                               new IndexBuffer(reinterpret_cast<const unsigned char*>(indices), sizeof(unsigned int), 6),
                               new VertexBufferLayout(vertexAttributes, 2));
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &_frameBufferID);
    glDeleteRenderbuffers(1, &_renderBufferID);
    delete _primitive;
    delete _framebufferTexture;
}

void FrameBuffer::Draw() const
{
    const auto vao = _primitive->GetVertexArrayObject();
    vao->Bind();
    _framebufferTexture->Bind(0);
    vao->Render();
    vao->Unbind();
}

void FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);
}

void FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
