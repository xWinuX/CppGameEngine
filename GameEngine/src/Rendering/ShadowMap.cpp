#include "GameEngine/Rendering/ShadowMap.h"

using namespace GameEngine::Rendering;

ShadowMap::ShadowMap(const glm::uvec2 size):
    _size(size)
{
    _shadowDepthMap = new Rendering::FrameBuffer(size);

    TextureParams textureParams;
    textureParams.FilterMode      = TextureFilterMode::Nearest;
    textureParams.WrapMode        = TextureWrapMode::ClampToBorder;
    textureParams.InternalFormat  = GL_DEPTH_COMPONENT;
    textureParams.Format          = GL_DEPTH_COMPONENT;
    textureParams.ChannelDataType = GL_FLOAT;

    _shadowMap = new Rendering::Texture2D(nullptr, size, textureParams);

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

Texture2D* ShadowMap::GetTexture() const { return _shadowMap; }

void      ShadowMap::Unbind() const { _shadowDepthMap->Unbind(); }

void      ShadowMap::SetPosition(const glm::vec3 position) { _position = position; }
void      ShadowMap::SetProjection(const glm::mat4 projection) { _projection = projection; }
glm::vec3 ShadowMap::GetPosition() const { return _position; }
glm::mat4 ShadowMap::GetProjection() const { return _projection; }
