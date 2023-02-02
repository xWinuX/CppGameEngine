#pragma once

#include "GameEngine/AssetDatabase.h"
#include "GameEngine/Rendering/Texture.h"
#include "GameEngine/Rendering/SpriteSet.h"
#include "GameEngine/Rendering/Model.h"
#include "GameEngine/Rendering/CubeMap.h"
#include "GameEngine/Audio/Sound.h"

namespace Asset
{
    enum class Texture : size_t
    {
        No,
        Black,
        White,
        NormalMapDefault,
        TheDude,
        Crate,
        CrateNormalMap
    };

    enum class Sprite : size_t
    {
        TheDude,
        DrL,
        GamerDude,
        Test,
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
        Dirty,
    };

    enum class Model : size_t
    {
        Cube,
        Suzanne,
        TheMissing,
        Sphere,
        HighPolyPlane
    };

    enum class Shader : size_t
    {
        Lit,
        Water,
        SpriteLit,
        PhysicsDebug,
        MSDFFont,
        VertexColor,
        FrameBuffer,
        Skybox,
    };

    enum class Material : size_t
    {
        Dude,
        Crate,
        PhysicsDebug,
        SpriteLit,
        Water,
        MSDFFont,
        VertexColor,
        Skybox,
    };

    enum class CubeMap : size_t
    {
        SkyBox,
    };
}

#define ADD_TEXTURE(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::Texture*>(Asset::Texture::id, asset)
#define ADD_CUBEMAP(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::CubeMap*>(Asset::CubeMap::id, asset)
#define ADD_SPRITE(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::SpriteSet*>(Asset::Sprite::id, asset)
#define ADD_FONT(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::Font*>(Asset::Font::id, asset)
#define ADD_MODEL(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::Model*>(Asset::Model::id, asset)
#define ADD_SOUND(id, asset) GameEngine::AssetDatabase::Add<Sound*>(Asset::Sound::id, asset)
#define ADD_SHADER(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::Shader*>(Asset::Shader::id, asset)
#define ADD_MATERIAL(id, asset) GameEngine::AssetDatabase::Add<GameEngine::Rendering::Material*>(Asset::Material::##id, asset)

#define GET_TEXTURE(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::Texture*>(Asset::Texture::id)
#define GET_CUBEMAP(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::CubeMap*>(Asset::CubeMap::id)
#define GET_SPRITE(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::SpriteSet*>(Asset::Sprite::id)
#define GET_FONT(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::Font*>(Asset::Font::id)
#define GET_MODEL(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::Model*>(Asset::Model::id)
#define GET_SOUND(id) GameEngine::AssetDatabase::Get<GameEngine::Audio::Sound*>(Asset::Sound::id)
#define GET_SHADER(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::Shader*>(Asset::Shader::id)
#define GET_MATERIAL(id) GameEngine::AssetDatabase::Get<GameEngine::Rendering::Material*>(Asset::Material::id)
