#include "GameEngine/Rendering/ShadowMap.h"

using namespace GameEngine::Rendering;

ShadowMap::ShadowMap(const glm::uvec2 size):
    _size(size)
{
    _shadowDepthMap = new Rendering::FrameBuffer(size);

    Texture::ImportSettings importSettings;
    importSettings.FilterMode      = Texture::Nearest;
    importSettings.WrapMode        = Texture::ClampToBorder;
    importSettings.InternalFormat  = GL_DEPTH_COMPONENT;
    importSettings.Format          = GL_DEPTH_COMPONENT;
    importSettings.ChannelDataType = GL_FLOAT;

    _shadowMap = new Rendering::Texture(nullptr, size, importSettings);

    _shadowDepthMap->AttachTexture(_shadowMap, GL_DEPTH_ATTACHMENT);

    glDrawBuffer(GL_NONE);

    glReadBuffer(GL_NONE);
    _shadowDepthMap->Unbind();
}

void ShadowMap::Bind() const
{
    glViewport(0, 0, _size.x, _size.y);
    _shadowDepthMap->Bind();
    glClear(GL_DEPTH_BUFFER_BIT);
}

Texture* ShadowMap::GetTexture() const { return _shadowMap; }

void      ShadowMap::Unbind() const { _shadowDepthMap->Unbind(); }

void      ShadowMap::SetPosition(const glm::vec3 position) { _position = position; }
void      ShadowMap::SetProjection(const glm::mat4 projection) { _projection = projection; }
glm::vec3 ShadowMap::GetPosition() const { return _position; }
glm::mat4 ShadowMap::GetProjection() const { return _projection; }
