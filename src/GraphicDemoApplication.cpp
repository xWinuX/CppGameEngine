#include "GraphicDemoApplication.h"

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
#include "glm/gtx/string_cast.hpp"
/*
#include <fmod.hpp>

FMOD::System* fmodSystem;*/

using namespace GameEngine;
using namespace GameEngine::Debug;
using namespace GameEngine::Audio;
using namespace GameEngine::Utils;
using namespace GameEngine::Rendering;
using namespace GameEngine::Components;
using namespace GameEngine::Physics;
using namespace GameEngine::Shapes;

// Textures 
Texture* noTexture;
Texture* blackTexture;
Texture* whiteTexture;
Texture* normalMapDefaultTexture;
Texture* theDudeTexture;
Texture* crateTexture;
Texture* crateNormalMapTexture;

// Sprite Textures
Texture* theDudeSpriteTexture;
Texture* drLSpriteTexture;
Texture* gamerDudeSpriteTexture;
Texture* testSpriteTexture;

Model* cubeModel;
Model* suzanneModel;
Model* theMissingModel;
Model* sphereModel;
Model* highPolyPlane;

Shader* litShader;
Shader* spriteShader;
Shader* spriteLitShader;
Shader* msdfFontShader;
Shader* waterShader;
Shader* physicsDebugShader;
Shader* vertexColorShader;

Material* spriteLitMaterial;
Material* dudeMaterial;
Material* crateMaterial;
Material* physicsMaterial;
Material* waterMaterial;
Material* msdfFontMaterial;
Material* vertexColorMaterial;

GameObject* cameraObject;
GameObject* redLightObject;
GameObject* rainbowLightObject;
GameObject* suzanneObject;
GameObject* theMissingObject;
GameObject* crateObject;
GameObject* childCrateObject;
GameObject* childOfChildCrateObject;

SpriteSet* theDudeSprite;
SpriteSet* drLSprite;
SpriteSet* gamerDudeSprite;
SpriteSet* testSprite;

SpriteAtlas* spriteAtlas;

Font* pixelFont;

Cube* cube;

Sound* dlSound;

void GraphicDemoApplication::Initialize(Scene& scene)
{
    dlSound = new Sound("res/audio/Test.mp3", true);
    
    // Fonts
    pixelFont = new Font("res/fonts/Roboto-Regular.ttf");

    // Textures
    noTexture               = new Texture("res/textures/NoTexture.png");
    blackTexture            = new Texture("res/textures/Black.png");
    whiteTexture            = new Texture("res/textures/White.png");
    normalMapDefaultTexture = new Texture("res/textures/NormalMapDefault.png");
    theDudeTexture          = new Texture("res/textures/TheDude.png");
    crateTexture            = new Texture("res/textures/Crate.jpg");
    crateNormalMapTexture   = new Texture("res/textures/CrateNormalMap.png");

    // Sprite Textures
    Texture::ImportSettings pixelArtTextureImportSettings;
    pixelArtTextureImportSettings.AnisotropyLevels = 0;
    pixelArtTextureImportSettings.MipMapLevels     = 0;
    pixelArtTextureImportSettings.FilterMode       = Texture::FilterMode::Nearest;

    theDudeSpriteTexture   = new Texture("res/sprites/TheDudeSprite.png", pixelArtTextureImportSettings);
    drLSpriteTexture       = new Texture("res/sprites/DrLSprite.png", pixelArtTextureImportSettings);
    gamerDudeSpriteTexture = new Texture("res/sprites/GamerDudeSprite.png", pixelArtTextureImportSettings);
    testSpriteTexture      = new Texture("res/sprites/TestSprite.png", pixelArtTextureImportSettings);

    theDudeSprite   = new SpriteSet(theDudeSpriteTexture, 2, glm::vec2(30, 49));
    drLSprite       = new SpriteSet(drLSpriteTexture);
    gamerDudeSprite = new SpriteSet(gamerDudeSpriteTexture);
    testSprite      = new SpriteSet(testSpriteTexture, 12, glm::uvec2(32, 32));

    spriteAtlas = new SpriteAtlas(glm::ivec2(1024), pixelArtTextureImportSettings);

    spriteAtlas->AddSprite(gamerDudeSprite);
    spriteAtlas->AddSprite(drLSprite);
    spriteAtlas->AddSprite(theDudeSprite);
    spriteAtlas->AddSprite(testSprite);

    spriteAtlas->Pack();

    cubeModel       = new Model("res/models/Cube.gltf");
    suzanneModel    = new Model("res/models/Suzanne.gltf");
    theMissingModel = new Model("res/models/TheMissing.gltf");
    sphereModel     = new Model("res/models/Sphere.gltf");
    highPolyPlane   = new Model("res/models/HighPolyPlane.gltf");

    cube = new Cube();
    
    UniformBuffer commonUniforms = UniformBuffer();
    commonUniforms.InitializeUniform<float>("u_Time", 0.0f, false);
    commonUniforms.InitializeUniform<glm::vec3>("u_ViewPosition", glm::zero<glm::vec3>(), false);
    commonUniforms.InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);
    commonUniforms.InitializeUniform<glm::mat4>("u_Transform", glm::identity<glm::mat4>(), false);

    UniformBuffer litUniforms = UniformBuffer();
    litUniforms.InitializeUniform<float>("u_Shininess", 0.7f);
    litUniforms.InitializeUniform<Texture*>("u_NormalMap", normalMapDefaultTexture);

    litUniforms.InitializeUniform<glm::vec4>("u_AmbientLightColor", glm::vec4(1.0));
    litUniforms.InitializeUniform<float>("u_AmbientLightIntensity", 0.3f);

    litUniforms.InitializeUniform<int>("u_NumPointLights", 0, false);
    litUniforms.InitializeUniform<std::vector<glm::vec3>*>("u_PointLightPositions", nullptr, false);
    litUniforms.InitializeUniform<std::vector<glm::vec4>*>("u_PointLightColors", nullptr, false);
    litUniforms.InitializeUniform<std::vector<float>*>("u_PointLightIntensities", nullptr, false);
    litUniforms.InitializeUniform<std::vector<float>*>("u_PointLightRanges", nullptr, false);

    UniformBuffer spriteUniforms = UniformBuffer();
    spriteUniforms.InitializeUniform<Texture*>("u_Texture", whiteTexture, false);

    #pragma region Default Shader
    litShader = new Shader("res/shaders/Lit/Lit.vert", "res/shaders/Lit/Lit.frag");
    litShader->GetUniformBuffer()->CopyFrom(&commonUniforms);
    litShader->GetUniformBuffer()->CopyFrom(&litUniforms);

    // Other
    litShader->InitializeUniform<glm::vec4>("u_ColorTint", glm::vec4(1.0f));
    litShader->InitializeUniform<Texture*>("u_Texture", whiteTexture);

    // Dude material
    dudeMaterial = new Material(litShader);
    dudeMaterial->GetUniformBuffer()->SetUniform("u_Texture", theDudeTexture);

    // Crate material
    crateMaterial = new Material(litShader);
    crateMaterial->GetUniformBuffer()->SetUniform("u_Texture", crateTexture);
    crateMaterial->GetUniformBuffer()->SetUniform("u_NormalMap", crateNormalMapTexture);
    crateMaterial->GetUniformBuffer()->SetUniform("u_NormalMapIntensity", 1.0f);
    #pragma endregion

    #pragma region Water Shader
    waterShader = new Shader("res/shaders/Water/Water.vert", "res/shaders/Water/Water.frag");
    waterShader->UniformBufferFromShader(litShader);

    // Material
    waterMaterial = new Material(waterShader);
    waterMaterial->SetTransparent(true);
    #pragma endregion

    #pragma region Sprite Lit Shader
    spriteLitShader = new Shader("res/shaders/SpriteLit/SpriteLit.vert", "res/shaders/SpriteLit/SpriteLit.frag");
    spriteLitShader->GetUniformBuffer()->CopyFrom(&commonUniforms);
    spriteLitShader->GetUniformBuffer()->CopyFrom(&spriteUniforms);
    spriteLitShader->GetUniformBuffer()->CopyFrom(&litUniforms);

    // Material
    spriteLitMaterial = new Material(spriteLitShader);
    spriteLitMaterial->SetCullFace(Material::CullFace::None);
    #pragma endregion

    #pragma region Physics Debug Shader
    physicsDebugShader = new Shader("res/shaders/PhysicsDebugShader.vsh", "res/shaders/PhysicsDebugShader.fsh");

    // Common
    physicsDebugShader->InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);

    // Material
    physicsMaterial = new Material(physicsDebugShader);
    physicsMaterial->SetCullFace(Material::None);
    physicsMaterial->SetRenderMode(Material::Wireframe);
    #pragma endregion

    #pragma region MSDFFont Shader
    msdfFontShader = new Shader("res/shaders/MSDFFont/MSDFFont.vert", "res/shaders/MSDFFont/MSDFFont.frag");
    msdfFontShader->GetUniformBuffer()->CopyFrom(&commonUniforms);
    msdfFontShader->GetUniformBuffer()->CopyFrom(&spriteUniforms);

    msdfFontMaterial = new Material(msdfFontShader);
    msdfFontMaterial->SetCullFace(Material::CullFace::None);
    #pragma endregion

    #pragma region VertexColor Shader
    vertexColorShader = new Shader("res/shaders/VertexColor/VertexColor.vert", "res/shaders/VertexColor/VertexColor.frag");
    vertexColorShader->GetUniformBuffer()->CopyFrom(&commonUniforms);
    vertexColorShader->InitializeUniform<Texture*>("u_Texture", crateTexture);

    vertexColorMaterial = new Material(vertexColorShader);
    #pragma endregion
    
    // Camera
    cameraObject = new GameObject();
    cameraObject->AddComponent(new Camera(60, 0.01f, 10000.0f));
    cameraObject->AddComponent(new AudioListener());
    scene.AddGameObject(cameraObject);

    // Red light
    redLightObject               = new GameObject();
    Transform* redLightTransform = redLightObject->GetTransform();
    redLightTransform->SetLocalPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    redLightTransform->SetLocalScale(glm::vec3(0.1f));
    redLightObject->AddComponent(new MeshRenderer(sphereModel->GetMesh(0), dudeMaterial));
    redLightObject->AddComponent(new PointLight(litShader, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 2.0f));
    scene.AddGameObject(redLightObject);

    // Rainbow light
    rainbowLightObject               = new GameObject();
    Transform* rainbowLightTransform = rainbowLightObject->GetTransform();
    rainbowLightTransform->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
    rainbowLightTransform->SetLocalScale(glm::vec3(0.1f));
    rainbowLightObject->AddComponent(new AudioSource(dlSound));
    rainbowLightObject->AddComponent(new MeshRenderer(sphereModel->GetMesh(0), dudeMaterial));
    rainbowLightObject->AddComponent(new PointLight(litShader, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 2.0f));
    scene.AddGameObject(rainbowLightObject);

    // Suzanne
    suzanneObject = new GameObject();
    suzanneObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 2.0f, 0.0f));
    // suzanneObject->AddComponent(new MeshRenderer(suzanneModel->GetMesh(0), dudeMaterial));
   // suzanneObject->AddComponent(new SpriteRenderer(pixelFont->GetSprite(), msdfFontMaterial));
    suzanneObject->AddComponent(new TextRenderer(pixelFont, msdfFontMaterial));
    scene.AddGameObject(suzanneObject);

    // The Missing
    theMissingObject = new GameObject();
    theMissingObject->AddComponent(new MeshRenderer(theMissingModel->GetMesh(0), {dudeMaterial, crateMaterial}, 2));
    theMissingObject->AddComponent(new MeshRenderer(theMissingModel->GetMesh(1), dudeMaterial));
    theMissingObject->AddComponent(new MeshRenderer(theMissingModel->GetMesh(2), dudeMaterial));
    scene.AddGameObject(theMissingObject);

    // Crate
    crateObject = new GameObject();
    crateObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, -1.5f, 0.0f));
    crateObject->AddComponent(new MeshRenderer(cube->GetMesh(), vertexColorMaterial));
    //crateObject->AddComponent(new SpriteRenderer(theDudeSprite, spriteLitMaterial));
    crateObject->AddComponent(new BoxCollider(glm::vec3(0.5f)));
    crateObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::DYNAMIC));
    scene.AddGameObject(crateObject);

    // Child crate
    childCrateObject = new GameObject();
    childCrateObject->GetTransform()->SetLocalPosition(glm::vec3(5.0f, 0.0f, 0.0f));
    childCrateObject->AddComponent(new MeshRenderer(cubeModel->GetMesh(0), crateMaterial));
    childCrateObject->SetParent(crateObject);

    // Child of child Crate
    childOfChildCrateObject = new GameObject();
    childOfChildCrateObject->GetTransform()->SetLocalPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    childOfChildCrateObject->AddComponent(new MeshRenderer(cubeModel->GetMesh(0), crateMaterial));
    childOfChildCrateObject->SetParent(childCrateObject);

    // Floor
    GameObject*                        floorObject    = new GameObject();
    GameEngine::Components::Transform* floorTransform = floorObject->GetTransform();
    floorTransform->SetLocalPosition(glm::vec3(0.0f, -2.0f, 0.0f));
    floorTransform->SetLocalScale(glm::vec3(2.0f, 2.0f, 2.0f));
    floorObject->AddComponent(new MeshRenderer(sphereModel->GetMesh(0), crateMaterial));
    floorObject->AddComponent(new BoxCollider(glm::vec3(5.0f, 0.5f, 5.0f)));
    floorObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::STATIC));
    scene.AddGameObject(floorObject);

    // Water
    GameObject* waterObject = new GameObject();
    waterObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, -2.0f, 0.0f));
   // waterObject->AddComponent(new MeshRenderer(highPolyPlane->GetMesh(0), waterMaterial));
    scene.AddGameObject(waterObject);

    // Setup physics debug
    PhysicsManager::SetDebugRendererMaterial(physicsMaterial);
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


    if (Input::GetKeyPressed(GLFW_KEY_M))
    {
        rainbowLightObject->GetComponent<AudioSource>()->PlayLooped();
    }
    
    // Change rainbow light color
    rainbowLightObject->GetComponent<PointLight>()->SetColor(glm::vec4(
                                                                       Math::Sin01(Time::GetTimeSinceStart() + 250),
                                                                       Math::Sin01(Time::GetTimeSinceStart() + 500),
                                                                       Math::Sin01(Time::GetTimeSinceStart() + 750),
                                                                       1.0f
                                                                      ));

    childCrateObject->GetTransform()->SetLocalScale(glm::vec3(2.0, 2.0, 2.0));

    // Rotate 
    theMissingObject->GetTransform()->Rotate(glm::vec3(0.0f, 0.0f, 45.0f * Time::GetDeltaTime()));
    suzanneObject->GetTransform()->Rotate(glm::vec3(0.0f, 45.0f * Time::GetDeltaTime(), 0.0f));

    // Rotate child crate to test hierarchy
    childCrateObject->GetTransform()->RotateLocal(glm::vec3(0.0f, 0.0f, 45.0f * Time::GetDeltaTime()));

    // Move lights
  //  rainbowLightObject->GetTransform()->SetLocalPosition(glm::vec3(sin(Time::GetTimeSinceStart()) * 7.0f, -1.0f, 0.0f));
    redLightObject->GetTransform()->SetLocalPosition(glm::vec3(0.0, -1.0f, sin(Time::GetTimeSinceStart()) * 7.0f));

    rainbowLightObject->GetTransform()->MoveLocal(cameraVelocity*10.0f);
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
