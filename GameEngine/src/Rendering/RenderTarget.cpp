#include "GameEngine/Rendering/RenderTarget.h"

GameEngine::Rendering::RenderTarget::RenderTarget(Shader* shader):
    _shader(shader),
    _screenQuad(Rendering::Primitives::ScreenQuad::GetPrimitive())
{
    _renderTextureImportSettings.FilterMode      = Texture::Nearest;
    _renderTextureImportSettings.WrapMode        = Texture::ClampToEdge;
    _renderTextureImportSettings.InternalFormat  = GL_RGB32F;
    _renderTextureImportSettings.Format          = GL_RGB;
    _renderTextureImportSettings.ChannelDataType = GL_FLOAT;

    CreateRenderingSetup(glm::uvec2(0.0f));
}

GameEngine::Rendering::RenderTarget::~RenderTarget()
{
    delete _frameBuffer;
    delete _renderBuffer;
    delete _renderTexture;
}

void GameEngine::Rendering::RenderTarget::Bind() { _frameBuffer->Bind(); }

void GameEngine::Rendering::RenderTarget::Unbind() const
{
    _frameBuffer->Unbind();
    _shader->Use();
    _shader->GetUniformStorage()->Apply();
    _renderTexture->Bind(0);
    _screenQuad->GetVertexArrayObject()->Bind();
    _screenQuad->GetVertexArrayObject()->Draw();
    _screenQuad->GetVertexArrayObject()->Unbind();
}

void GameEngine::Rendering::RenderTarget::CreateRenderingSetup(const glm::uvec2 size)
{
    _frameBuffer   = new FrameBuffer(size);
    _renderBuffer  = new RenderBuffer(size, GL_DEPTH24_STENCIL8);
    _renderTexture = new Texture(nullptr, size, _renderTextureImportSettings);

    _frameBuffer->AttachTexture(_renderTexture, GL_COLOR_ATTACHMENT0);
    _frameBuffer->BindRenderBuffer(_renderBuffer, GL_DEPTH_STENCIL_ATTACHMENT);
}

void GameEngine::Rendering::RenderTarget::ResizeFrameBuffer(const glm::uvec2 size)
{
    delete _frameBuffer;
    delete _renderBuffer;
    delete _renderTexture;

    CreateRenderingSetup(size);
}
