#pragma once

#include "GameEngine/AssetDatabase.h"
#include "GameEngine/Rendering/Texture2D.h"
#include "GameEngine/Rendering/SpriteSet.h"
#include "GameEngine/Rendering/Model.h"
#include "GameEngine/Rendering/CubeMap.h"
#include "GameEngine/Audio/Sound.h"

namespace Asset
{
    enum class Texture2D : size_t
    {
        No,
        Black,
        White,
        NormalMapDefault,
        TheDude,
        Crate,
        CrateNormalMap,
        Grass,
        Dirt,
        Sand
    };

    enum class Sprite : size_t
    {
        TheDude,
        GamerDudeWalkRight,
        GamerDudeWalkLeft,
    };

    enum class Font : size_t
    {
        Roboto
    };

    enum class Sound : size_t
    {
        Hey,
        BackgroundMusic,
    };

    enum class Model : size_t
    {
        Cube,
        Suzanne,
        TheMissing,
        Sphere,
        WaterPlane,
        Island,
    };

    enum class Shader : size_t
    {
        Lit,
        Island,
        Water,
        SpriteLit,
        PhysicsDebug,
        MSDFFont,
        VertexColor,
        FrameBuffer,
        Skybox,
        ShadowMap,
        ShadowMapSprite,
    };

    enum class Material : size_t
    {
        Dude,
        Porcelain,
        Mirror,
        Crate,
        Island,
        PhysicsDebug,
        SpriteLit,
        Water,
        MSDFFont,
        VertexColor,
        Skybox,
        FrameBuffer
    };

    enum class CubeMap : size_t
    {
        SkyBox,
    };

    enum class SpriteAtlas : size_t
    {
        Default
    };
}

#define ADD_TEXTURE_2D(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::Texture2D*>(Asset::Texture2D::id, asset)
#define ADD_CUBEMAP(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::CubeMap*>(Asset::CubeMap::id, asset)
#define ADD_SPRITE(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::SpriteSet*>(Asset::Sprite::id, asset)
#define ADD_FONT(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::Font*>(Asset::Font::id, asset)
#define ADD_MODEL(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::Model*>(Asset::Model::id, asset)
#define ADD_SOUND(id, asset) GameEngine::AssetDatabase::Add<Sound*>(Asset::Sound::id, asset)
#define ADD_SHADER(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::Shader*>(Asset::Shader::id, asset)
#define ADD_MATERIAL(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::Material*>(Asset::Material::##id, asset)
#define ADD_SPRITE_ATLAS(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::SpriteAtlas*>(Asset::SpriteAtlas::##id, asset)

#define GET_TEXTURE_2D(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::Texture2D*>(Asset::Texture2D::id)
#define GET_CUBEMAP(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::CubeMap*>(Asset::CubeMap::id)
#define GET_SPRITE(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::SpriteSet*>(Asset::Sprite::id)
#define GET_FONT(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::Font*>(Asset::Font::id)
#define GET_MODEL(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::Model*>(Asset::Model::id)
#define GET_SOUND(id) GameEngine::AssetDatabase::Get<GameEngine::Audio::Sound*>(Asset::Sound::id)
#define GET_SHADER(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::Shader*>(Asset::Shader::id)
#define GET_MATERIAL(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::Material*>(Asset::Material::id)
#define GET_SPRITE_ATLAS(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::SpriteAtlas*>(Asset::SpriteAtlas::id)
