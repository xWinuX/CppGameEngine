#include "GraphicDemoApplication.h"

#include "Asset.h"
#include "CarstenBehaviour.h"
#include "GameEngine/Components/BoxCollider.h"
#include "GameEngine/Components/Camera.h"
#include "GameEngine/Components/MeshRenderer.h"
#include "GameEngine/Components/PointLight.h"
#include "GameEngine/Components/Rigidbody.h"
#include "GameEngine/Components/TextRenderer.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/Window.h"
#include "GameEngine/Input.h"
#include "GameEngine/Physics/PhysicsManager.h"
#include "GameEngine/Rendering/Font.h"
#include "GameEngine/Rendering/Material.h"
#include "GameEngine/Rendering/Model.h"
#include "GameEngine/Rendering/Shader.h"
#include "GameEngine/Rendering/SpriteSet.h"
#include "GameEngine/Rendering/Texture.h"
#include "GameEngine/Rendering/SpriteAtlas.h"
#include "GameEngine/Utils/Math.h"
#include "GameEngine/Shapes/Cube.h"
#include "GameEngine/Time.h"
#include "GameEngine/Audio/AudioManager.h"
#include "GameEngine/Audio/Sound.h"
#include "GameEngine/Components/AudioListener.h"
#include "GameEngine/Components/AudioSource.h"
#include "GameEngine/Components/CapsuleCollider.h"
#include "GameEngine/Components/SpriteRenderer.h"
#include "glm/gtx/string_cast.hpp"
#include "Prefabs/CarstenPrefab.h"


using namespace GameEngine;
using namespace GameEngine::Debug;
using namespace GameEngine::Audio;
using namespace GameEngine::Utils;
using namespace GameEngine::Rendering;
using namespace GameEngine::Components;
using namespace GameEngine::Physics;
using namespace GameEngine::Shapes;

GameObject* cameraObject;
GameObject* redLightObject;
GameObject* rainbowLightObject;
GameObject* suzanneObject;
GameObject* theMissingObject;
GameObject* crateObject;
GameObject* childCrateObject;
GameObject* childOfChildCrateObject;
GameObject* carstenObject;

SpriteAtlas* spriteAtlas;

Cube* cube;

void GraphicDemoApplication::LoadTextures()
{
    ADD_TEXTURE(No, new Texture("res/textures/NoTexture.png"));
    ADD_TEXTURE(Black, new Texture("res/textures/Black.png"));
    ADD_TEXTURE(White, new Texture("res/textures/White.png"));
    Texture::ImportSettings importSettings;
    importSettings.FilterMode = Texture::Nearest;
    ADD_TEXTURE(NormalMapDefault, new Texture("res/textures/NormalMapDefault.png", importSettings));
    ADD_TEXTURE(TheDude, new Texture("res/textures/TheDude.png"));
    ADD_TEXTURE(Crate, new Texture("res/textures/Crate.jpg"));
    ADD_TEXTURE(CrateNormalMap, new Texture("res/textures/CrateNormalMap.png"));
}

void GraphicDemoApplication::LoadSprites()
{
    Texture::ImportSettings pixelArtTextureImportSettings;
    pixelArtTextureImportSettings.AnisotropyLevels = 0;
    pixelArtTextureImportSettings.MipMapLevels     = 0;
    pixelArtTextureImportSettings.FilterMode       = Texture::FilterMode::Nearest;

    Texture* theDudeSpriteTexture          = new Texture("res/sprites/TheDudeSprite.png", pixelArtTextureImportSettings);
    Texture* drLSpriteTexture              = new Texture("res/sprites/DrLSprite.png", pixelArtTextureImportSettings);
    Texture* gamerDudeSpriteTexture        = new Texture("res/sprites/GamerDudeSprite.png", pixelArtTextureImportSettings);
    Texture* testSpriteTexture             = new Texture("res/sprites/TestSprite.png", pixelArtTextureImportSettings);
    Texture* carstenWalkRightSpriteTexture = new Texture("res/sprites/CarstenWalkRight.png", pixelArtTextureImportSettings);
    Texture* carstenWalkLeftSpriteTexture  = new Texture("res/sprites/CarstenWalkLeft.png", pixelArtTextureImportSettings);

    SpriteSet* theDude          = ADD_SPRITE(TheDude, new SpriteSet(theDudeSpriteTexture, 2, glm::vec2(30, 49)));
    SpriteSet* drL              = ADD_SPRITE(DrL, new SpriteSet(drLSpriteTexture));
    SpriteSet* gamerDude        = ADD_SPRITE(GamerDude, new SpriteSet(gamerDudeSpriteTexture));
    SpriteSet* test             = ADD_SPRITE(Test, new SpriteSet(testSpriteTexture, 12, glm::uvec2(32, 32)));
    SpriteSet* carstenWalkRight = ADD_SPRITE(CarstenWalkRight, new SpriteSet(carstenWalkRightSpriteTexture, 6, glm::uvec2(119, 190), 90));
    SpriteSet* carstenWalkLeft  = ADD_SPRITE(CarstenWalkLeft, new SpriteSet(carstenWalkLeftSpriteTexture, 6, glm::uvec2(119, 190), 90));

    spriteAtlas = new SpriteAtlas(glm::ivec2(1024), pixelArtTextureImportSettings);

    spriteAtlas->AddSprite(theDude);
    spriteAtlas->AddSprite(drL);
    spriteAtlas->AddSprite(gamerDude);
    spriteAtlas->AddSprite(test);
    spriteAtlas->AddSprite(carstenWalkRight);
    spriteAtlas->AddSprite(carstenWalkLeft);

    spriteAtlas->Pack();
}

void GraphicDemoApplication::LoadFonts() const { ADD_FONT(Roboto, new Font("res/fonts/Roboto-Regular.ttf")); }

void GraphicDemoApplication::LoadSounds() const
{
    ADD_SOUND(Dirty, new Sound("res/audio/Test.mp3", true));
    ADD_SOUND(Hey, new Sound("res/audio/CarstenHey.ogg", true));
}

void GraphicDemoApplication::LoadModels() const
{
    ADD_MODEL(Cube, new Model("res/models/Cube.gltf"));
    ADD_MODEL(Suzanne, new Model("res/models/Suzanne.gltf"));
    ADD_MODEL(TheMissing, new Model("res/models/TheMissing.gltf"));
    ADD_MODEL(Sphere, new Model("res/models/Sphere.gltf"));
    ADD_MODEL(HighPolyPlane, new Model("res/models/HighPolyPlane.gltf"));
}

void GraphicDemoApplication::LoadShaders() const
{
    #pragma region Template Uniforms
    UniformStorage commonUniforms = UniformStorage();
    commonUniforms.InitializeUniform<float>("u_Time", 0.0f, false);
    commonUniforms.InitializeUniform<glm::vec3>("u_ViewPosition", glm::zero<glm::vec3>(), false);
    commonUniforms.InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);
    commonUniforms.InitializeUniform<glm::mat4>("u_Transform", glm::identity<glm::mat4>(), false);

    UniformStorage litUniforms = UniformStorage();
    litUniforms.InitializeUniform<float>("u_Shininess", 0.7f);
    litUniforms.InitializeUniform<Texture*>("u_NormalMap", GET_TEXTURE(NormalMapDefault));

    litUniforms.InitializeUniform<glm::vec4>("u_AmbientLightColor", glm::vec4(1.0));
    litUniforms.InitializeUniform<float>("u_AmbientLightIntensity", 0.3f);

    litUniforms.InitializeUniform<int>("u_NumPointLights", 0, false);
    litUniforms.InitializeUniform<std::vector<glm::vec3>*>("u_PointLightPositions", nullptr, false);
    litUniforms.InitializeUniform<std::vector<glm::vec4>*>("u_PointLightColors", nullptr, false);
    litUniforms.InitializeUniform<std::vector<float>*>("u_PointLightIntensities", nullptr, false);
    litUniforms.InitializeUniform<std::vector<float>*>("u_PointLightRanges", nullptr, false);

    UniformStorage spriteUniforms = UniformStorage();
    spriteUniforms.InitializeUniform<Texture*>("u_Texture", GET_TEXTURE(White), false);
    #pragma endregion

    // Lit
    Shader* litShader = ADD_SHADER(Lit, new Shader("res/shaders/Lit/Lit.vert", "res/shaders/Lit/Lit.frag"));
    litShader->GetUniformStorage()->CopyFrom(&commonUniforms);
    litShader->GetUniformStorage()->CopyFrom(&litUniforms);

    litShader->InitializeUniform<glm::vec4>("u_ColorTint", glm::vec4(1.0f));
    litShader->InitializeUniform<Texture*>("u_Texture", GET_TEXTURE(White));

    // Water
    Shader* waterShader = ADD_SHADER(Water, new Shader("res/shaders/Water/Water.vert", "res/shaders/Water/Water.frag"));
    waterShader->UniformStorageFromShader(litShader);

    // Sprite Lit
    Shader* spriteLitShader = ADD_SHADER(SpriteLit, new Shader("res/shaders/SpriteLit/SpriteLit.vert", "res/shaders/SpriteLit/SpriteLit.frag"));
    spriteLitShader->GetUniformStorage()->CopyFrom(&commonUniforms);
    spriteLitShader->GetUniformStorage()->CopyFrom(&spriteUniforms);
    spriteLitShader->GetUniformStorage()->CopyFrom(&litUniforms);

    // Physics Debug
    Shader* physicsDebugShader = ADD_SHADER(PhysicsDebug, new Shader("res/shaders/PhysicsDebugShader.vsh", "res/shaders/PhysicsDebugShader.fsh"));
    physicsDebugShader->InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);

    // MSDF Font
    Shader* msdfFontShader = ADD_SHADER(MSDFFont, new Shader("res/shaders/MSDFFont/MSDFFont.vert", "res/shaders/MSDFFont/MSDFFont.frag"));
    msdfFontShader->GetUniformStorage()->CopyFrom(&commonUniforms);
    msdfFontShader->GetUniformStorage()->CopyFrom(&spriteUniforms);

    // Vertex Color
    Shader* vertexColorShader = ADD_SHADER(VertexColor, new Shader("res/shaders/VertexColor/VertexColor.vert", "res/shaders/VertexColor/VertexColor.frag"));
    vertexColorShader->GetUniformStorage()->CopyFrom(&commonUniforms);
    vertexColorShader->InitializeUniform<Texture*>("u_Texture", GET_TEXTURE(Crate));

    // Frame Buffer
    Shader* frameBufferShader = ADD_SHADER(FrameBuffer, new Shader("res/shaders/FrameBuffer/FrameBuffer.vert", "res/shaders/FrameBuffer/FrameBuffer.frag"));
}

void GraphicDemoApplication::LoadMaterials() const
{
    // Dude
    Material* dudeMaterial = ADD_MATERIAL(Dude, new Material(GET_SHADER(Lit)));
    dudeMaterial->GetUniformStorage()->SetUniform("u_Texture", GET_TEXTURE(TheDude));

    // Crate
    Material* crateMaterial = ADD_MATERIAL(Crate, new Material(GET_SHADER(Lit)));

    crateMaterial->GetUniformStorage()->SetUniform("u_Texture", GET_TEXTURE(Crate));
    crateMaterial->GetUniformStorage()->SetUniform("u_NormalMap", GET_TEXTURE(CrateNormalMap));
    crateMaterial->GetUniformStorage()->SetUniform("u_NormalMapIntensity", 1.0f);

    // Physics Debug
    Material* physicsMaterial = ADD_MATERIAL(PhysicsDebug, new Material(GET_SHADER(PhysicsDebug)));
    physicsMaterial->SetCullFace(Material::None);
    physicsMaterial->SetRenderMode(Material::Wireframe);

    // Sprite Lit
    Material* spriteLitMaterial = ADD_MATERIAL(SpriteLit, new Material(GET_SHADER(SpriteLit)));
    spriteLitMaterial->SetCullFace(Material::CullFace::None);

    // Water
    Material* waterMaterial = ADD_MATERIAL(Water, new Material(GET_SHADER(Water)));
    waterMaterial->SetTransparent(true);

    // MSDF Font
    Material* msdfFontMaterial = ADD_MATERIAL(MSDFFont, new Material(GET_SHADER(MSDFFont)));
    msdfFontMaterial->SetCullFace(Material::CullFace::None);

    // Vertex Color
    ADD_MATERIAL(VertexColor, new Material(GET_SHADER(VertexColor)));
}

void GraphicDemoApplication::LoadAssets()
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

    cube = new Cube();

    // Camera
    cameraObject = new GameObject();
    cameraObject->AddComponent(new Camera(60, 0.01f, 10000.0f, GET_SHADER(FrameBuffer)));
    cameraObject->AddComponent(new AudioListener());
    scene.AddGameObject(cameraObject);

    // Carsten
    CarstenPrefab carstenPrefab = CarstenPrefab();
    for (unsigned int i = 0; i < 20000; i++)
    {
        GameObject*     gameObject     = carstenPrefab.Instantiate();
        const glm::vec2 randomPosition = glm::diskRand(30.0f);
        gameObject->GetTransform()->SetPosition(glm::vec3(randomPosition.x, 0.0f, randomPosition.y));
        gameObject->GetTransform()->SetLocalScale(glm::linearRand(0.25f, 5.0f) * glm::vec3(1.0));
        scene.AddGameObject(gameObject);
    }
    
    // Red light
    redLightObject               = new GameObject();
    Transform* redLightTransform = redLightObject->GetTransform();
    redLightTransform->SetLocalPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    redLightTransform->SetLocalScale(glm::vec3(0.1f));
    redLightObject->AddComponent(new MeshRenderer(GET_MODEL(Sphere)->GetMesh(0), GET_MATERIAL(Dude)));
    //redLightObject->AddComponent(new PointLight(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 2.0f));
    scene.AddGameObject(redLightObject);

    // Rainbow light
    rainbowLightObject               = new GameObject();
    Transform* rainbowLightTransform = rainbowLightObject->GetTransform();
    rainbowLightTransform->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
    rainbowLightTransform->SetLocalScale(glm::vec3(0.1f));
    rainbowLightObject->AddComponent(new AudioSource(GET_SOUND(Dirty)));
    rainbowLightObject->AddComponent(new MeshRenderer(GET_MODEL(Sphere)->GetMesh(0), GET_MATERIAL(Dude)));
    rainbowLightObject->AddComponent(new PointLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 5.0f));
    scene.AddGameObject(rainbowLightObject);

    // Suzanne
    suzanneObject = new GameObject();
    suzanneObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 2.0f, 0.0f));
    // suzanneObject->AddComponent(new MeshRenderer(suzanneModel->GetMesh(0), dudeMaterial));
    // suzanneObject->AddComponent(new SpriteRenderer(pixelFont->GetSprite(), msdfFontMaterial));
    //suzanneObject->AddComponent(new TextRenderer(GET_FONT(Roboto), GET_MATERIAL(MSDFFont)));
    scene.AddGameObject(suzanneObject);

    // The Missing
    theMissingObject = new GameObject();
    theMissingObject->GetTransform()->SetLocalScale(glm::vec3(5));
    theMissingObject->AddComponent(new MeshRenderer(GET_MODEL(TheMissing)->GetMesh(0), {GET_MATERIAL(Dude), GET_MATERIAL(Crate)}, 2));
    theMissingObject->AddComponent(new MeshRenderer(GET_MODEL(TheMissing)->GetMesh(1), GET_MATERIAL(Dude)));
    theMissingObject->AddComponent(new MeshRenderer(GET_MODEL(TheMissing)->GetMesh(2), GET_MATERIAL(Dude)));
    scene.AddGameObject(theMissingObject);

    // Crate
    crateObject = new GameObject();
    crateObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, -1.5f, 0.0f));
    crateObject->AddComponent(new MeshRenderer(GET_MODEL(Cube)->GetMesh(0), GET_MATERIAL(Crate)));
    crateObject->AddComponent(new SpriteRenderer(GET_SPRITE(TheDude), GET_MATERIAL(SpriteLit)));
    crateObject->AddComponent(new BoxCollider(glm::vec3(0.5f)));
    crateObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::DYNAMIC));
    scene.AddGameObject(crateObject);

    // Child crate
    childCrateObject = new GameObject();
    childCrateObject->GetTransform()->SetLocalPosition(glm::vec3(5.0f, 0.0f, 0.0f));
    childCrateObject->AddComponent(new MeshRenderer(GET_MODEL(Cube)->GetMesh(0), GET_MATERIAL(Crate)));
    childCrateObject->SetParent(crateObject);

    // Child of child Crate
    childOfChildCrateObject = new GameObject();
    childOfChildCrateObject->GetTransform()->SetLocalPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    childOfChildCrateObject->AddComponent(new MeshRenderer(GET_MODEL(Cube)->GetMesh(0), GET_MATERIAL(Crate)));
    childOfChildCrateObject->SetParent(childCrateObject);

    // Floor
    GameObject*                        floorObject    = new GameObject();
    GameEngine::Components::Transform* floorTransform = floorObject->GetTransform();
    floorTransform->SetLocalPosition(glm::vec3(0.0f, -2.0f, 0.0f));
    floorTransform->SetLocalScale(glm::vec3(2.0f, 2.0f, 2.0f));
    floorObject->AddComponent(new MeshRenderer(GET_MODEL(Sphere)->GetMesh(0), GET_MATERIAL(Crate)));
    floorObject->AddComponent(new BoxCollider(glm::vec3(5.0f, 0.5f, 5.0f)));
    floorObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::STATIC));
    scene.AddGameObject(floorObject);

    // Water
    GameObject* waterObject = new GameObject();
    waterObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, -2.0f, 0.0f));
    // waterObject->AddComponent(new MeshRenderer(highPolyPlane->GetMesh(0), waterMaterial));
    scene.AddGameObject(waterObject);

    // Setup physics debug
    PhysicsManager::SetDebugRendererMaterial(GET_MATERIAL(PhysicsDebug));
    PhysicsManager::ToggleDebugWireframe();
}

void GraphicDemoApplication::CustomRun()
{
    // Toggle physics debug wireframe
    if (Input::GetKeyPressed(GLFW_KEY_P)) { PhysicsManager::ToggleDebugWireframe(); }

    // Camera movement
    glm::vec4 cameraVelocity = glm::vec4(0.0f);
    if (Input::GetKeyDown(GLFW_KEY_D)) { cameraVelocity.x += 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_A)) { cameraVelocity.x -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_W)) { cameraVelocity.z -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_S)) { cameraVelocity.z += 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_LEFT_SHIFT)) { cameraVelocity.y -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_SPACE)) { cameraVelocity.y += 5.0f * Time::GetDeltaTime(); }

    // Crate movement
    glm::vec4 crateVelocity = glm::vec4(0.0f);
    if (Input::GetKeyDown(GLFW_KEY_RIGHT)) { crateVelocity.x += 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_LEFT)) { crateVelocity.x -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_UP)) { crateVelocity.z -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_DOWN)) { crateVelocity.z += 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_C)) { crateVelocity.y -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_V)) { crateVelocity.y += 5.0f * Time::GetDeltaTime(); }

    // Close window if escape key is pressed
    if (Input::GetKeyPressed(GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(Application::_window.GetGlWindow(), true); }


    if (Input::GetKeyPressed(GLFW_KEY_M)) { rainbowLightObject->GetComponent<AudioSource>()->PlayLooped(); }

    // Change rainbow light color
    rainbowLightObject->GetComponent<PointLight>()->SetColor(glm::vec4(
                                                                       Math::Sin01(Time::GetTimeSinceStart() + 250),
                                                                       Math::Sin01(Time::GetTimeSinceStart() + 500),
                                                                       Math::Sin01(Time::GetTimeSinceStart() + 750),
                                                                       1.0f
                                                                      ));

    childCrateObject->GetTransform()->SetLocalScale(glm::vec3(2.0, 2.0, 2.0));

    // Rotate 
    // theMissingObject->GetTransform()->Rotate(glm::vec3(0.0f, 0.0f, 45.0f * Time::GetDeltaTime()));
    suzanneObject->GetTransform()->Rotate(glm::vec3(0.0f, 45.0f * Time::GetDeltaTime(), 0.0f));

    // Rotate child crate to test hierarchy
    childCrateObject->GetTransform()->RotateLocal(glm::vec3(0.0f, 0.0f, 45.0f * Time::GetDeltaTime()));

    // Move lights
    //  rainbowLightObject->GetTransform()->SetLocalPosition(glm::vec3(sin(Time::GetTimeSinceStart()) * 7.0f, -1.0f, 0.0f));
    redLightObject->GetTransform()->SetLocalPosition(glm::vec3(0.0, -1.0f, sin(Time::GetTimeSinceStart()) * 7.0f));

    rainbowLightObject->GetTransform()->Move(cameraVelocity);
    // Move crate
    //crateObject->GetComponent<Rigidbody>()->ApplyForce(crateVelocity * 100.0f);
    //crateObject->GetComponent<Rigidbody>()->ApplyTorque(crateVelocity * 100.0f);

    // Move camera
    cameraObject->GetTransform()->Move(crateVelocity);


    GameEngine::Debug::Log::Message(glm::to_string(rainbowLightObject->GetTransform()->GetPosition()));
    GameEngine::Debug::Log::Message(glm::to_string(rainbowLightObject->GetTransform()->GetLocalPosition()));
    GameEngine::Debug::Log::Message(glm::to_string(cameraObject->GetTransform()->GetPosition()));
    GameEngine::Debug::Log::Message(glm::to_string(cameraObject->GetTransform()->GetLocalPosition()));
    std::cout << "FPS: " << std::to_string(1 / Time::GetDeltaTime()) << std::endl;
}
