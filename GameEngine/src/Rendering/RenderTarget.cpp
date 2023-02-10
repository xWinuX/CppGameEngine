#include "GameEngine/Rendering/RenderTarget.h"
#include "GameEngine/Rendering/RenderablePrimitive.h"
#include "GameEngine/Rendering/VertexArrayObject.h"

#include "GameEngine/Rendering/Primitives/ScreenQuad.h"

using namespace GameEngine::Rendering;

RenderTarget::RenderTarget(Shader* shader):
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

RenderTarget::~RenderTarget()
{
    delete _frameBuffer;
    delete _renderBuffer;
    delete _renderTexture;
}

bool RenderTarget::GetRenderShadows() const { return _renderShadows; }
void RenderTarget::SetRenderShadows(const bool renderShadows) { _renderShadows = renderShadows; }

void RenderTarget::Bind()
{
    const glm::ivec2 size = _renderTexture->GetSize();
    glViewport(0, 0, size.x, size.y);
    _frameBuffer->Bind();
    _frameBuffer->Clear();
}

void RenderTarget::Unbind() const
{
    _frameBuffer->Unbind();
    _shader->Use();
    _shader->GetUniformStorage()->Apply();
    _renderTexture->Bind(0);
    _screenQuad->GetVertexArrayObject()->Bind();
    _screenQuad->GetVertexArrayObject()->Draw();
    _screenQuad->GetVertexArrayObject()->Unbind();
}

void RenderTarget::CreateRenderingSetup(const glm::uvec2 size)
{
    _frameBuffer   = new FrameBuffer(size, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    _renderBuffer  = new RenderBuffer(size, GL_DEPTH24_STENCIL8);
    _renderTexture = new Texture(nullptr, size, _renderTextureImportSettings);

    _frameBuffer->AttachTexture(_renderTexture, GL_COLOR_ATTACHMENT0);
    _frameBuffer->AttachRenderBuffer(_renderBuffer, GL_DEPTH_STENCIL_ATTACHMENT);
}

void RenderTarget::ResizeFrameBuffer(const glm::uvec2 size)
{
    delete _frameBuffer;
    delete _renderBuffer;
    delete _renderTexture;

    CreateRenderingSetup(size);
}

void RenderTarget::AddActiveLayer(const Layer layer) { _layerMask |= static_cast<int>(layer); }

void RenderTarget::RemoveActiveLayer(const Layer layer) { _layerMask &= ~static_cast<int>(layer); }

bool RenderTarget::HasActiveLayer(Layer layer) const { return (_layerMask & static_cast<int>(layer)) == static_cast<int>(layer); }
