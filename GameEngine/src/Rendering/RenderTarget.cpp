#include "GameEngine/Rendering/RenderTarget.h"


GameEngine::Rendering::RenderTarget::RenderTarget(Shader* shader):
    _frameBuffer(new FrameBuffer(glm::uvec2(0.0f))),
    _shader(shader) { }

void GameEngine::Rendering::RenderTarget::Bind() { _frameBuffer->Bind(); }

void GameEngine::Rendering::RenderTarget::Unbind() const
{
    _frameBuffer->Unbind();
    _shader->Use();
    _shader->GetUniformStorage()->Apply();
    _frameBuffer->Draw();
}

void GameEngine::Rendering::RenderTarget::ResizeFrameBuffer(const glm::uvec2 newSize)
{
    delete _frameBuffer;
    _frameBuffer = new FrameBuffer(newSize);
}
