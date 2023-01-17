#include "RenderableSprite.h"

#include "../Utils/Time.h"

GameEngine::Rendering::RenderableSprite::RenderableSprite(Sprite* sprite, Material* material):
    _sprite(sprite),
    _material(material) {}

unsigned GameEngine::Rendering::RenderableSprite::GetVertexSize() { return sizeof(Sprite::VertexData); }

void GameEngine::Rendering::RenderableSprite::CopyQuadData(unsigned char* destination)
{
    memcpy(destination, _sprite->GetQuadData(static_cast<unsigned int>(floor(_frameIndex))), GetVertexSize() * 4);
}

void GameEngine::Rendering::RenderableSprite::OnBeforeDraw()
{
    if (_transform == nullptr) { return; }

    _material->GetUniformBuffer()->SetUniformInstant<glm::mat4>("u_Transform", _transform->GetTRS());
}

void GameEngine::Rendering::RenderableSprite::Update()
{
    _frameIndex = fmod(_frameIndex + Time::GetDeltaTime()*_framesPerSecond, static_cast<float>(_sprite->GetNumFrames()));
}

GameEngine::Rendering::Material* GameEngine::Rendering::RenderableSprite::GetMaterial() { return _material; }
GameEngine::Rendering::Texture*  GameEngine::Rendering::RenderableSprite::GetTexture() { return _sprite->GetTextures()[0]; }

float GameEngine::Rendering::RenderableSprite::GetFrameIndex() const { return _frameIndex; }
void  GameEngine::Rendering::RenderableSprite::SetFrameIndex(const float frameIndex) { _frameIndex = frameIndex; }
void  GameEngine::Rendering::RenderableSprite::SetFramesPerSecond(const float framesPerSecond) { _framesPerSecond = framesPerSecond; }
void  GameEngine::Rendering::RenderableSprite::SetTransform(Components::Transform* transform) { _transform = transform; }
