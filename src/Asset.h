#pragma once

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
        CarstenWalkRight,
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
    };
}

#define ADD_TEXTURE(id, asset) AssetDatabase::Add<Texture*>(Asset::Texture::id, asset)
#define ADD_SPRITE(id, asset) AssetDatabase::Add<SpriteSet*>(Asset::Sprite::id, asset)
#define ADD_FONT(id, asset) AssetDatabase::Add<Font*>(Asset::Font::id, asset)
#define ADD_MODEL(id, asset) AssetDatabase::Add<Model*>(Asset::Model::id, asset)
#define ADD_SOUND(id, asset) AssetDatabase::Add<Sound*>(Asset::Sound::id, asset)
#define ADD_SHADER(id, asset) AssetDatabase::Add<Shader*>(Asset::Shader::id, asset)
#define ADD_MATERIAL(id, asset) AssetDatabase::Add<Material*>(Asset::Material::##id, asset)

#define GET_TEXTURE(id) AssetDatabase::Get<Texture*>(Asset::Texture::id)
#define GET_SPRITE(id) AssetDatabase::Get<SpriteSet*>(Asset::Sprite::id)
#define GET_FONT(id) AssetDatabase::Get<Font*>(Asset::Font::id)
#define GET_MODEL(id) AssetDatabase::Get<Model*>(Asset::Model::id)
#define GET_SOUND(id) AssetDatabase::Get<Sound*>(Asset::Sound::id)
#define GET_SHADER(id) AssetDatabase::Get<Shader*>(Asset::Shader::id)
#define GET_MATERIAL(id) AssetDatabase::Get<Material*>(Asset::Material::id)
