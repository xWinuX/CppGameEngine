#include "GameEngine/Rendering/CascadedShadowMap.h"

#include "GameEngine/Rendering/Texture2DArray.h"

using namespace GameEngine::Rendering;

CascadedShadowMap::CascadedShadowMap(const glm::uvec2 size):
    _size(size)
{
    _shadowDepthMap = new Rendering::FrameBuffer(size);

    TextureParams textureParams;
    textureParams.FilterMode      = TextureFilterMode::Nearest;
    textureParams.WrapMode        = TextureWrapMode::ClampToBorder;
    textureParams.InternalFormat  = GL_DEPTH_COMPONENT32F;
    textureParams.Format          = GL_DEPTH_COMPONENT;
    textureParams.ChannelDataType = GL_FLOAT;

    _shadowMap = new Rendering::Texture2DArray(size, 5, textureParams);

    _shadowDepthMap->AttachTexture(_shadowMap, GL_DEPTH_ATTACHMENT);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);


    _shadowDepthMap->Unbind();
}

void CascadedShadowMap::Bind() const
{
    glViewport(0, 0, _size.x, _size.y);
    _shadowDepthMap->Bind();
    glClear(GL_DEPTH_BUFFER_BIT);
}

Texture2DArray* CascadedShadowMap::GetTexture() const { return _shadowMap; }

void      CascadedShadowMap::Unbind() const { _shadowDepthMap->Unbind(); }

void      CascadedShadowMap::SetPosition(const glm::vec3 position) { _position = position; }
void      CascadedShadowMap::SetProjection(const glm::mat4 projection) { _projection = projection; }
glm::vec3 CascadedShadowMap::GetPosition() const { return _position; }
glm::mat4 CascadedShadowMap::GetProjection() const { return _projection; }
