#include "RenderTarget.h"

GameEngine::Rendering::RenderTarget::RenderTarget(Shader* shader):
    _frameBuffer(new FrameBuffer()),
    _shader(shader) { }

void GameEngine::Rendering::RenderTarget::Bind() const { _frameBuffer->Bind(); }

void GameEngine::Rendering::RenderTarget::Unbind() const
{
    _frameBuffer->Unbind();
    glDisable(GL_DEPTH_TEST);
    _shader->Use();
    _frameBuffer->Draw();
}
