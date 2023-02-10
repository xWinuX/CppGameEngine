#include "ShadowMap.h"

GameEngine::Rendering::ShadowMap::ShadowMap(const glm::uvec2 size)
{
    _shadowDepthMap = new Rendering::FrameBuffer(size);

    Texture::ImportSettings importSettings;
    importSettings.FilterMode      = Texture::Nearest;
    importSettings.WrapMode        = Texture::Repeat;
    importSettings.InternalFormat  = GL_DEPTH_COMPONENT;
    importSettings.Format          = GL_DEPTH_COMPONENT;
    importSettings.ChannelDataType = GL_FLOAT;

    _shadowMap = new Rendering::Texture(nullptr, size, importSettings);

    _shadowDepthMap->AttachTexture(_shadowMap, GL_DEPTH_ATTACHMENT);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    _shadowDepthMap->Unbind();
}
