#include "GraphicDemoApplication.h"

#include "Asset.h"
#include "GameEngine/Components/DirectionalLight.h"

#include "Components/POVCameraController.h"
#include "Components/GameManager.h"
#include "Components/POVCharacterController.h"
#include "Components/RainbowLight.h"
#include "Components/Rotator.h"
#include "GameEngine/Components/BoxCollider.h"
#include "GameEngine/Components/Camera.h"
#include "GameEngine/Components/MeshRenderer.h"
#include "GameEngine/Components/PointLight.h"
#include "GameEngine/Components/Rigidbody.h"
#include "GameEngine/Components/TextRenderer.h"
#include "GameEngine/Components/Transform.h"

#include "GameEngine/Physics/PhysicsManager.h"
#include "GameEngine/Rendering/Font.h"
#include "GameEngine/Rendering/Material.h"
#include "GameEngine/Rendering/Model.h"
#include "GameEngine/Rendering/Shader.h"
#include "GameEngine/Rendering/SpriteSet.h"
#include "GameEngine/Rendering/Texture2D.h"
#include "GameEngine/Rendering/SpriteAtlas.h"
#include "GameEngine/Utils/Math.h"
#include "GameEngine/Audio/AudioManager.h"
#include "GameEngine/Audio/Sound.h"
#include "GameEngine/Components/AudioListener.h"
#include "GameEngine/Components/AudioSource.h"
#include "GameEngine/Components/CapsuleCollider.h"
#include "GameEngine/Components/MeshCollider.h"
#include "GameEngine/Components/SpriteRenderer.h"
#include "GameEngine/Rendering/Renderer.h"
#include "glm/gtc/random.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Prefabs/CratePrefab.h"
#include "Prefabs/GamerDudePrefab.h"

using namespace GameEngine;
using namespace GameEngine::Debug;
using namespace GameEngine::Audio;
using namespace GameEngine::Utils;
using namespace GameEngine::Rendering;
using namespace GameEngine::Components;
using namespace GameEngine::Physics;

void GraphicDemoApplication::LoadTextures() const
{
    TextureParams nearestNeighbour;
    nearestNeighbour.FilterMode = TextureFilterMode::Nearest;
    ADD_TEXTURE_2D(NormalMapDefault, new Texture2D("res/textures/NormalMapDefault.png", nearestNeighbour));

    ADD_TEXTURE_2D(No, new Texture2D("res/textures/NoTexture.png"));
    ADD_TEXTURE_2D(Black, new Texture2D("res/textures/Black.png"));
    ADD_TEXTURE_2D(White, new Texture2D("res/textures/White.png"));
    ADD_TEXTURE_2D(TheDude, new Texture2D("res/textures/TheDude.png"));
    ADD_TEXTURE_2D(Crate, new Texture2D("res/textures/Crate.jpg"));
    ADD_TEXTURE_2D(CrateNormalMap, new Texture2D("res/textures/CrateNormalMap.png"));

    TextureParams mipMapLinear;
    mipMapLinear.FilterMode = TextureFilterMode::LinearMipMap;

    ADD_TEXTURE_2D(Grass, new Texture2D("res/textures/Grass.png", mipMapLinear));
    ADD_TEXTURE_2D(Dirt, new Texture2D("res/textures/Dirt.png", mipMapLinear));
    ADD_TEXTURE_2D(Sand, new Texture2D("res/textures/Sand.png",mipMapLinear));

    ADD_CUBEMAP(SkyBox, new CubeMap("res/textures/Skybox/Skybox", ".png"));
}

void GraphicDemoApplication::LoadSprites() const
{
    TextureParams pixelArtTextureImportSettings;
    pixelArtTextureImportSettings.AnisotropyLevels = 0;
    pixelArtTextureImportSettings.MipMapLevels     = 0;
    pixelArtTextureImportSettings.FilterMode       = TextureFilterMode::Nearest;

    Texture2D* theDudeSpriteTexture            = new Texture2D("res/sprites/TheDudeSprite.png", pixelArtTextureImportSettings);
    Texture2D* gamerDudeWalkRightSpriteTexture = new Texture2D("res/sprites/GamerDudeWalkRight.png", pixelArtTextureImportSettings);
    Texture2D* gamerDudeWalkLeftSpriteTexture  = new Texture2D("res/sprites/GamerDudeWalkLeft.png", pixelArtTextureImportSettings);

    SpriteSet* theDude = ADD_SPRITE(TheDude, new SpriteSet(theDudeSpriteTexture, 2, glm::vec2(30, 49)));

    Sprite::AdditionalInfo additionalInfo;
    additionalInfo.PixelsPerUnit  = 100;
    additionalInfo.Origin         = glm::vec2(0.5f, 0.5f);
    SpriteSet* gamerDudeWalkRight = ADD_SPRITE(GamerDudeWalkRight, new SpriteSet(gamerDudeWalkRightSpriteTexture, 6, glm::uvec2(119, 190), additionalInfo));
    SpriteSet* gamerDudeWalkLeft  = ADD_SPRITE(GamerDudeWalkLeft, new SpriteSet(gamerDudeWalkLeftSpriteTexture, 6, glm::uvec2(119, 190), additionalInfo));

    SpriteAtlas* spriteAtlas = ADD_SPRITE_ATLAS(Default, new SpriteAtlas(glm::ivec2(1024), pixelArtTextureImportSettings));

    spriteAtlas->AddSprite(theDude);
    spriteAtlas->AddSprite(gamerDudeWalkRight);
    spriteAtlas->AddSprite(gamerDudeWalkLeft);
    spriteAtlas->Pack();
}

void GraphicDemoApplication::LoadFonts() const { ADD_FONT(Roboto, new Font("res/fonts/Roboto-Regular.ttf")); }

void GraphicDemoApplication::LoadSounds() const
{
    ADD_SOUND(Hey, new Sound("res/audio/Hey.ogg", true));
    ADD_SOUND(BackgroundMusic, new Sound("res/audio/BackgroundMusic.mp3", false));
}

void GraphicDemoApplication::LoadModels() const
{
    ADD_MODEL(Cube, new Model("res/models/Cube.gltf"));
    ADD_MODEL(Suzanne, new Model("res/models/Suzanne.gltf"));
    ADD_MODEL(TheMissing, new Model("res/models/TheMissing.gltf"));
    ADD_MODEL(Sphere, new Model("res/models/Sphere.gltf"));
    ADD_MODEL(WaterPlane, new Model("res/models/WaterPlane.gltf"));
    ADD_MODEL(Island, new Model("res/models/Island.gltf", true));
}

void GraphicDemoApplication::LoadShaders() const
{
    #pragma region Template Uniforms
    UniformStorage commonUniforms = UniformStorage();
    commonUniforms.InitializeUniform<float>("u_Time", 0.0f, false);
    commonUniforms.InitializeUniform<glm::mat4>("u_Transform", glm::identity<glm::mat4>(), false);

    UniformStorage litUniforms = UniformStorage();
    litUniforms.InitializeUniform<float>("u_Smoothness", 0.0f);
    litUniforms.InitializeUniform<float>("u_Metallicness", 0.0f);
    litUniforms.InitializeUniform<Texture2D*>("u_NormalMap", GET_TEXTURE_2D(NormalMapDefault));
    litUniforms.InitializeUniform<CubeMap*>("u_SkyboxCubeMap", GET_CUBEMAP(SkyBox));

    #pragma endregion

    // Lit
    Shader* litShader = ADD_SHADER(Lit, new Shader("res/shaders/Lit/Lit.vert", "res/shaders/Lit/Lit.frag"));
    litShader->GetUniformStorage()->CopyFrom(&commonUniforms);
    litShader->GetUniformStorage()->CopyFrom(&litUniforms);

    litShader->InitializeUniform<glm::vec4>("u_ColorTint", glm::vec4(1.0f));
    litShader->InitializeUniform<Texture2D*>("u_Texture", GET_TEXTURE_2D(White));

    // Island
    Shader* islandShader = ADD_SHADER(Island, new Shader("res/shaders/Island/Island.vert", "res/shaders/Island/Island.frag"));
    islandShader->UniformStorageFromShader(litShader);
    islandShader->InitializeUniform<Texture2D*>("u_TextureRed", GET_TEXTURE_2D(Dirt));
    islandShader->InitializeUniform<Texture2D*>("u_TextureGreen", GET_TEXTURE_2D(Grass));
    islandShader->InitializeUniform<Texture2D*>("u_TextureBlue", GET_TEXTURE_2D(Sand));
    islandShader->InitializeUniform<float>("u_TilingFactor", 0.1f);

    // Water
    Shader* waterShader = ADD_SHADER(Water, new Shader("res/shaders/Water/Water.vert", "res/shaders/Water/Water.frag"));
    waterShader->UniformStorageFromShader(litShader);

    waterShader->InitializeUniform<glm::vec3>("u_WaveOrigin", glm::zero<glm::vec3>());
    waterShader->InitializeUniform<float>("u_WaveSpeed", 2.0f);
    waterShader->InitializeUniform<float>("u_WaveAmplitude", 0.2f);
    waterShader->InitializeUniform<float>("u_WaveFrequency", 0.3f);

    // Sprite Lit
    Shader* spriteLitShader = ADD_SHADER(SpriteLit, new Shader("res/shaders/SpriteLit/SpriteLit.vert", "res/shaders/SpriteLit/SpriteLit.frag"));
    spriteLitShader->GetUniformStorage()->CopyFrom(&commonUniforms);
    spriteLitShader->GetUniformStorage()->CopyFrom(&litUniforms);

    // Physics Debug
    Shader* physicsDebugShader = ADD_SHADER(PhysicsDebug, new Shader("res/shaders/PhysicsDebug/PhysicsDebug.vert", "res/shaders/PhysicsDebug/PhysicsDebug.frag"));
    physicsDebugShader->InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);

    // MSDF Font
    Shader* msdfFontShader = ADD_SHADER(MSDFFont, new Shader("res/shaders/MSDFFont/MSDFFont.vert", "res/shaders/MSDFFont/MSDFFont.frag"));
    msdfFontShader->GetUniformStorage()->CopyFrom(&commonUniforms);

    // Vertex Color
    Shader* vertexColorShader = ADD_SHADER(VertexColor, new Shader("res/shaders/VertexColor/VertexColor.vert", "res/shaders/VertexColor/VertexColor.frag"));
    vertexColorShader->GetUniformStorage()->CopyFrom(&commonUniforms);
    vertexColorShader->InitializeUniform<Texture2D*>("u_Texture", GET_TEXTURE_2D(Crate));

    // Frame Buffer
    Shader* frameBufferShader = ADD_SHADER(FrameBuffer, new Shader("res/shaders/FrameBuffer/FrameBuffer.vert", "res/shaders/FrameBuffer/FrameBuffer.frag"));
    frameBufferShader->GetUniformStorage()->CopyFrom(&commonUniforms);
    frameBufferShader->InitializeUniform<int>("u_BloomBlurSize", 3);
    frameBufferShader->InitializeUniform<float>("u_BloomBlurOffset", 2);

    // Skybox
    Shader* skyboxShader = ADD_SHADER(Skybox, new Shader("res/shaders/Skybox/Skybox.vert", "res/shaders/Skybox/Skybox.frag"));
    skyboxShader->GetUniformStorage()->CopyFrom(&commonUniforms);
    skyboxShader->InitializeUniform<CubeMap*>("u_CubeMap", GET_CUBEMAP(SkyBox));
    skyboxShader->InitializeUniform<float>("u_Exposure", 1.2f);

    // Shadow Map
    Shader* shadowMapShader = ADD_SHADER(ShadowMap,
                                         new Shader("res/shaders/ShadowMap/Shadowmap.vert","res/shaders/ShadowMap/Shadowmap.frag", "res/shaders/ShadowMap/Shadowmap.geom"));
    shadowMapShader->GetUniformStorage()->CopyFrom(&commonUniforms);

    // Shadow Map
    Shader* shadowMapSpriteShader = ADD_SHADER(ShadowMapSprite,
                                               new Shader("res/shaders/ShadowMapSprite/ShadowMapSprite.vert","res/shaders/ShadowMapSprite/ShadowMapSprite.frag",
                                                   "res/shaders/ShadowMapSprite/ShadowMapSprite.geom"));
    shadowMapSpriteShader->GetUniformStorage()->CopyFrom(&commonUniforms);
    shadowMapSpriteShader->InitializeUniform<Texture2D*>("u_Texture", GET_TEXTURE_2D(Crate));


    Renderer::SetShadowShader(shadowMapShader);
    Renderer::SetShadowSpriteShader(shadowMapSpriteShader);
}

void GraphicDemoApplication::LoadMaterials() const
{
    // Dude
    Material* dudeMaterial = ADD_MATERIAL(Dude, new Material("Dude", GET_SHADER(Lit)));
    dudeMaterial->GetUniformStorage()->SetUniform<Texture2D*>("u_Texture", GET_TEXTURE_2D(TheDude));
    dudeMaterial->GetUniformStorage()->SetUniform<float>("u_Smoothness", 1.0);

    // Crate
    Material* crateMaterial = ADD_MATERIAL(Crate, new Material("Crate", GET_SHADER(Lit)));

    crateMaterial->GetUniformStorage()->SetUniform("u_Texture", GET_TEXTURE_2D(Crate));
    crateMaterial->GetUniformStorage()->SetUniform("u_NormalMap", GET_TEXTURE_2D(CrateNormalMap));
    crateMaterial->GetUniformStorage()->SetUniform("u_NormalMapIntensity", 1.0f);

    // Porcelain 
    Material* porcelainMaterial = ADD_MATERIAL(Porcelain, new Material("Porcelain", GET_SHADER(Lit)));
    porcelainMaterial->GetUniformStorage()->SetUniform<float>("u_Smoothness", 1.0f);

    // Porcelain 
    Material* mirrorMaterial = ADD_MATERIAL(Mirror, new Material("Mirror", GET_SHADER(Lit)));
    mirrorMaterial->GetUniformStorage()->SetUniform<float>("u_Smoothness", 1.0);
    mirrorMaterial->GetUniformStorage()->SetUniform<float>("u_Metallicness", 1.0);

    // Island
    ADD_MATERIAL(Island, new Material("Island", GET_SHADER(Island)));

    // Physics Debug
    Material* physicsMaterial = ADD_MATERIAL(PhysicsDebug, new Material("PhysicsDebug", GET_SHADER(PhysicsDebug)));
    physicsMaterial->SetCullFace(Material::None);
    physicsMaterial->SetRenderMode(Material::Wireframe);

    // Sprite Lit
    Material* spriteLitMaterial = ADD_MATERIAL(SpriteLit, new Material("Sprite Lit", GET_SHADER(SpriteLit)));
    spriteLitMaterial->SetCullFace(Material::CullFace::None);

    // Water
    Material* waterMaterial = ADD_MATERIAL(Water, new Material("Water", GET_SHADER(Water)));
    waterMaterial->GetUniformStorage()->SetUniform<float>("u_Smoothness", 1.0);
    waterMaterial->GetUniformStorage()->SetUniform<float>("u_Metallicness", 1.0);
    waterMaterial->SetCullFace(Material::None);
    waterMaterial->SetTransparent(true);

    // MSDF Font
    Material* msdfFontMaterial = ADD_MATERIAL(MSDFFont, new Material("MSDF Font", GET_SHADER(MSDFFont)));
    msdfFontMaterial->SetCullFace(Material::CullFace::None);
    msdfFontMaterial->SetTransparent(true);

    // Vertex Color
    ADD_MATERIAL(VertexColor, new Material("Vertex Colors", GET_SHADER(VertexColor)));

    // Frame Buffer
    ADD_MATERIAL(FrameBuffer, new Material("Frame Buffer", GET_SHADER(FrameBuffer)));

    // Skybox
    Material* skyboxMaterial = ADD_MATERIAL(Skybox, new Material("Skybox", GET_SHADER(Skybox)));

    skyboxMaterial->SetCullFace(Material::Front);
    skyboxMaterial->SetDepthFunc(Material::DepthFunc::LEqual);
}

void GraphicDemoApplication::LoadAssets() const
{
    LoadFonts();
    LoadSounds();
    LoadTextures();
    LoadSprites();
    LoadModels();
    LoadShaders();
    LoadMaterials();
}

void GraphicDemoApplication::Initialize(Scene& scene)
{
    LoadAssets();

    // Game Manager
    GameObject* gameManagerObject = new GameObject("Game Manager");
    gameManagerObject->AddComponent(new GameManager());
    gameManagerObject->AddComponent(new AudioSource(GET_SOUND(BackgroundMusic), true, true));
    gameManagerObject->AddComponent(new TextRenderer(GET_FONT(Roboto), GET_MATERIAL(MSDFFont)));
    gameManagerObject->GetComponent<AudioSource>()->SetVolume(0.05f);

    // Player
    GameObject* playerObject = new GameObject("Player");
    playerObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 7.0f, 0.0f));

    playerObject->AddComponent(new CapsuleCollider());
    playerObject->AddComponent(new Rigidbody());
    playerObject->AddComponent(new CharacterController());
    playerObject->AddComponent(new POVCharacterController());
    playerObject->AddComponent(new MeshRenderer(GET_MODEL(Cube)->GetMesh(0), GET_MATERIAL(Crate)));

    // Camera
    GameObject* cameraObject = new GameObject("Camera");
    cameraObject->AddComponent(new Camera(60, 0.1f, 500.0f, GET_MATERIAL(FrameBuffer), GET_MATERIAL(Skybox)));
    cameraObject->AddComponent(new POVCameraController());
    cameraObject->AddComponent(new AudioListener());

    playerObject->GetComponent<POVCharacterController>()->SetCameraTransform(cameraObject->GetComponent<Transform>());
    cameraObject->GetComponent<POVCameraController>()->SetFollowTransform(playerObject->GetTransform());

    // Island
    GameObject* islandObject = new GameObject("Island");
    islandObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, -10.0f, 0.0f));

    islandObject->AddComponent(new MeshRenderer(GET_MODEL(Island)->GetMesh(0), GET_MATERIAL(Island)));
    islandObject->AddComponent(new MeshCollider(GET_MODEL(Island)->GetMesh(0)));
    islandObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::STATIC));

    // Water
    GameObject* waterObject = new GameObject("Water");
    waterObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, -9.0f, 0.0f));
    waterObject->AddComponent(new MeshRenderer(GET_MODEL(WaterPlane)->GetMesh(0), GET_MATERIAL(Water)));

    // Directional Light
    GameObject* directionalLight = new GameObject("Directional Light");
    directionalLight->GetTransform()->SetRotation(glm::quat(glm::vec3(-1.0f, 0.0f, 0.0f)));
    directionalLight->AddComponent(new DirectionalLight(true, glm::vec4(1.0f), 0.6f));

    // Point Light
    for (unsigned int i = 0; i < 6; i++)
    {
        GameObject*     pointLight          = new GameObject("Point Light");
        Transform*      pointLightTransform = pointLight->GetTransform();
        const glm::vec2 randomPosition      = glm::diskRand(50.0f);
        pointLightTransform->SetLocalPosition(glm::vec3(randomPosition.x, 0.0f, randomPosition.y));
        pointLightTransform->SetLocalScale(glm::vec3(0.1f));
        pointLight->AddComponent(new MeshRenderer(GET_MODEL(Sphere)->GetMesh(0), GET_MATERIAL(Porcelain)));
        pointLight->AddComponent(new PointLight(glm::vec4(abs(glm::sphericalRand(1.0f)), 0.5f), glm::linearRand(5.0f, 30.0f), glm::linearRand(0.5f, 2.0f)));
    }

    // Rainbow light
    GameObject* rainbowLightObject    = new GameObject("Rainbow Light");
    Transform*  rainbowLightTransform = rainbowLightObject->GetTransform();
    rainbowLightTransform->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
    rainbowLightTransform->SetLocalScale(glm::vec3(0.1f));
    rainbowLightObject->AddComponent(new MeshRenderer(GET_MODEL(Sphere)->GetMesh(0), GET_MATERIAL(Porcelain)));
    rainbowLightObject->AddComponent(new PointLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 15.0f, 1.0f));
    rainbowLightObject->AddComponent(new RainbowLight());

    // Suzanne
    GameObject* suzanneObject = new GameObject("Suzanne");
    suzanneObject->GetTransform()->SetLocalPosition(glm::vec3(6.0f, 0.0, -15.0f));
    suzanneObject->GetTransform()->SetLocalScale(glm::vec3(5.0f));
    suzanneObject->AddComponent(new MeshRenderer(GET_MODEL(Suzanne)->GetMesh(0), GET_MATERIAL(Porcelain)));
    suzanneObject->AddComponent(new Rotator());

    // The Missing
    GameObject* theMissingObject = new GameObject("The Missing");
    theMissingObject->GetTransform()->SetLocalScale(glm::vec3(35));
    theMissingObject->GetTransform()->SetLocalRotation(glm::quat(glm::vec3(0.2f, 0.3f, 1.0f)));
    theMissingObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, -40.0f, -130.0f));
    theMissingObject->AddComponent(new MeshRenderer(GET_MODEL(TheMissing)->GetMesh(0), {GET_MATERIAL(Porcelain), GET_MATERIAL(Dude)}, 2));
    theMissingObject->AddComponent(new MeshRenderer(GET_MODEL(TheMissing)->GetMesh(1), GET_MATERIAL(Porcelain)));
    theMissingObject->AddComponent(new MeshRenderer(GET_MODEL(TheMissing)->GetMesh(2), GET_MATERIAL(Mirror)));

    // Gamer Dude Spawner
    GamerDudePrefab gamerDudePrefab = GamerDudePrefab();
    for (unsigned int i = 0; i < 20; i++)
    {
        const GameObject* gameObject     = gamerDudePrefab.Instantiate();
        const glm::vec2   randomPosition = glm::diskRand(100.0f);
        gameObject->GetTransform()->SetPosition(glm::vec3(randomPosition.x, 100.0f, randomPosition.y));
        gameObject->GetTransform()->SetLocalScale(glm::linearRand(0.2f, 4.0f) * glm::vec3(1.0));
    }

    // Crate
    CratePrefab cratePrefab = CratePrefab();
    for (unsigned int i = 0; i < 20; i++)
    {
        const glm::vec2   randomPosition = glm::diskRand(10.0f);
        const GameObject* crateObject    = cratePrefab.Instantiate();
        crateObject->GetTransform()->SetPosition(glm::vec3(randomPosition.x, 20.0f, randomPosition.y));
    }


    // Setup physics debug
    PhysicsManager::SetDebugRendererMaterial(GET_MATERIAL(PhysicsDebug));
}
