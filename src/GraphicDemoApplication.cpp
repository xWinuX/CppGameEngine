#include "GraphicDemoApplication.h"

#include <glm/ext/quaternion_common.hpp>
#include <reactphysics3d/reactphysics3d.h>

#include "GameEngine/Components/BoxCollider.h"
#include "GameEngine/Components/Camera.h"
#include "GameEngine/Components/MeshRenderer.h"
#include "GameEngine/Components/PointLight.h"
#include "GameEngine/Components/Rigidbody.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/Core/Window.h"
#include "GameEngine/Input/Input.h"
#include "GameEngine/Physics/Physics.h"
#include "GameEngine/Rendering/Material.h"
#include "GameEngine/Rendering/Model.h"
#include "GameEngine/Rendering/Renderer.h"
#include "GameEngine/Rendering/Shader.h"
#include "GameEngine/Rendering/Texture.h"
#include "GameEngine/Utils/Math.h"
#include "GameEngine/Shapes/Cube.h"
#include "GameEngine/Utils/Time.h"
#include "glm/gtx/string_cast.hpp"

using namespace GameEngine::Debug;
using namespace GameEngine::Utils;
using namespace GameEngine::Core;
using namespace GameEngine::Rendering;
using namespace GameEngine::Components;
using namespace GameEngine::Physics;
using namespace GameEngine::Input;
using namespace GameEngine::Shapes;

Texture* noTexture;
Texture* blackTexture;
Texture* whiteTexture;
Texture* normalMapDefaultTexture;
Texture* theDudeTexture;
Texture* crateTexture;
Texture* crateNormalMapTexture;

Model* cubeModel;
Model* suzanneModel;
Model* theMissingModel;
Model* sphereModel;
Model* highPolyPlane;

Shader* defaultShader;
Shader* waterShader;
Shader* physicsDebugShader;
Shader* vertexColorShader;

Material* vertexColorMaterial;
Material* dudeMaterial;
Material* crateMaterial;
Material* physicsMaterial;
Material* waterMaterial;

GameObject* cameraObject;
GameObject* redLightObject;
GameObject* rainbowLightObject;
GameObject* suzanneObject;
GameObject* theMissingObject;
GameObject* crateObject;
GameObject* childCrateObject;
GameObject* childOfChildCrateObject;

void GraphicDemoApplication::Initialize(Scene& scene)
{
    noTexture               = new Texture("res/textures/NoTexture.png");
    blackTexture            = new Texture("res/textures/Black.png");
    whiteTexture            = new Texture("res/textures/White.png");
    normalMapDefaultTexture = new Texture("res/textures/NormalMapDefault.png");
    theDudeTexture          = new Texture("res/textures/TheDude.png");
    crateTexture            = new Texture("res/textures/Crate.jpg");
    crateNormalMapTexture   = new Texture("res/textures/CrateNormalMap.png");

    cubeModel       = new Model("res/models/Cube.gltf");
    suzanneModel    = new Model("res/models/Suzanne.gltf");
    theMissingModel = new Model("res/models/TheMissing.gltf");
    sphereModel     = new Model("res/models/Sphere.gltf");
    highPolyPlane   = new Model("res/models/HighPolyPlane.gltf");
    
    // TODO: somehow make initialized uniforms copyable so i don't have to copy paste code
    #pragma region Default Shader
    defaultShader = new Shader("res/shaders/Default/Default.vert", "res/shaders/Default/Default.frag");

    // Common
    defaultShader->InitializeUniform<float>("u_Time", 0.0f, false);
    defaultShader->InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);
    defaultShader->InitializeUniform<glm::mat4>("u_Transform", glm::identity<glm::mat4>(), false);

    // Lighting
    defaultShader->InitializeUniform<glm::vec4>("u_AmbientLightColor", glm::vec4(1.0));
    defaultShader->InitializeUniform<float>("u_AmbientLightIntensity", 0.5f);

    defaultShader->InitializeUniform<int>("u_NumPointLights", 0, false);
    defaultShader->InitializeUniform<std::vector<glm::vec3>*>("u_PointLightPositions", nullptr, false);
    defaultShader->InitializeUniform<std::vector<glm::vec4>*>("u_PointLightColors", nullptr, false);
    defaultShader->InitializeUniform<std::vector<float>*>("u_PointLightIntensities", nullptr, false);
    defaultShader->InitializeUniform<std::vector<float>*>("u_PointLightRanges", nullptr, false);

    // Other
    defaultShader->InitializeUniform<glm::vec4>("u_ColorTint", glm::vec4(1.0f));
    defaultShader->InitializeUniform<Texture*>("u_Texture", noTexture);
    defaultShader->InitializeUniform<Texture*>("u_NormalMap", normalMapDefaultTexture);
    defaultShader->InitializeUniform<float>("u_NormalMapIntensity", 1.0f);
    
    // Dude material
    dudeMaterial = new Material(defaultShader);
    dudeMaterial->GetUniformBuffer()->SetUniform("u_Texture", theDudeTexture);

    // Crate material
    crateMaterial = new Material(defaultShader);
    crateMaterial->GetUniformBuffer()->SetUniform("u_Texture", crateTexture);
    crateMaterial->GetUniformBuffer()->SetUniform("u_NormalMap", crateNormalMapTexture);
    crateMaterial->GetUniformBuffer()->SetUniform("u_NormalMapIntensity", 1.0f);
    #pragma endregion

    #pragma region Physics Debug Shader
    physicsDebugShader = new Shader("res/shaders/PhysicsDebugShader.vsh", "res/shaders/PhysicsDebugShader.fsh");
    physicsDebugShader->InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);

    // Material
    physicsMaterial = new Material(physicsDebugShader);
    physicsMaterial->SetCullFace(Material::None);
    physicsMaterial->SetRenderMode(Material::Wireframe);
    #pragma endregion

    #pragma region Water Shader
    waterShader = new Shader("res/shaders/Water/Water.vert", "res/shaders/Water/Water.frag");
    waterShader->InitializeUniform<float>("u_Time", 0.0f, false);

    // Common
    waterShader->InitializeUniform<float>("u_Time", 0.0f, false);
    waterShader->InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);
    waterShader->InitializeUniform<glm::mat4>("u_Transform", glm::identity<glm::mat4>(), false);

    // Lighting
    waterShader->InitializeUniform<glm::vec4>("u_AmbientLightColor", glm::vec4(1.0));
    waterShader->InitializeUniform<float>("u_AmbientLightIntensity", 0.5f);

    waterShader->InitializeUniform<int>("u_NumPointLights", 0, false);
    waterShader->InitializeUniform<std::vector<glm::vec3>*>("u_PointLightPositions", nullptr, false);
    waterShader->InitializeUniform<std::vector<glm::vec4>*>("u_PointLightColors", nullptr, false);
    waterShader->InitializeUniform<std::vector<float>*>("u_PointLightIntensities", nullptr, false);
    waterShader->InitializeUniform<std::vector<float>*>("u_PointLightRanges", nullptr, false);

    // Other
    waterShader->InitializeUniform<glm::vec4>("u_ColorTint", glm::vec4(0.0, 0.0, 1.0f, 1.0));
    waterShader->InitializeUniform<Texture*>("u_Texture", whiteTexture);
    waterShader->InitializeUniform<Texture*>("u_NormalMap", normalMapDefaultTexture);
    waterShader->InitializeUniform<float>("u_NormalMapIntensity", 1.0f);

    // Material
    waterMaterial = new Material(waterShader);
    waterMaterial->SetTransparent(true);
    #pragma endregion

    #pragma region Vertex Color Shader
    vertexColorShader = new Shader("res/shaders/VertexColor/VertexColor.vert", "res/shaders/VertexColor/VertexColor.frag");

    vertexColorShader->InitializeUniform<float>("u_Time", 0.0f, false);
    vertexColorShader->InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);
    vertexColorShader->InitializeUniform<glm::mat4>("u_Transform", glm::identity<glm::mat4>(), false);

    vertexColorShader->InitializeUniform<Texture*>("u_Texture", whiteTexture);

    vertexColorMaterial = new Material(vertexColorShader);
    vertexColorMaterial->GetUniformBuffer()->SetUniform("u_Texture", crateTexture);
    #pragma endregion

    // Camera
    cameraObject = new GameObject();
    cameraObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 0.0f, 8.0f));
    cameraObject->AddComponent(new Camera(60, 0.01f, 100.0f));
    scene.AddGameObject(cameraObject);

    // Red light
    redLightObject               = new GameObject();
    Transform* redLightTransform = redLightObject->GetTransform();
    redLightTransform->SetLocalPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    redLightTransform->SetLocalScale(glm::vec3(0.1f));
    redLightObject->AddComponent(new MeshRenderer(sphereModel->GetMesh(0), dudeMaterial));
    redLightObject->AddComponent(new PointLight(defaultShader, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 2.0f));
    scene.AddGameObject(redLightObject);

    // Rainbow light
    rainbowLightObject               = new GameObject();
    Transform* rainbowLightTransform = rainbowLightObject->GetTransform();
    rainbowLightTransform->SetLocalPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
    rainbowLightTransform->SetLocalScale(glm::vec3(0.1f));
    rainbowLightObject->AddComponent(new MeshRenderer(sphereModel->GetMesh(0), dudeMaterial));
    rainbowLightObject->AddComponent(new PointLight(defaultShader, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 2.0f));
    scene.AddGameObject(rainbowLightObject);

    // Suzanne
    suzanneObject = new GameObject();
    suzanneObject->GetTransform()->SetLocalPosition(glm::vec3(3.0f, 0.0f, 0.0f));
    suzanneObject->AddComponent(new MeshRenderer(suzanneModel->GetMesh(0), dudeMaterial));
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
    crateObject->GetTransform()->SetLocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
    crateObject->AddComponent(new MeshRenderer(cubeModel->GetMesh(0), crateMaterial));
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
    floorTransform->SetLocalScale(glm::vec3(10.0f, 1.0f, 5.0f));
    floorObject->AddComponent(new MeshRenderer(cubeModel->GetMesh(0), crateMaterial));
    floorObject->AddComponent(new BoxCollider(glm::vec3(5.0f, 0.5f, 5.0f)));
    floorObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::STATIC));
    scene.AddGameObject(floorObject);

    // Water
    GameObject* waterObject = new GameObject();
    waterObject->GetTransform()->SetLocalPosition(glm::vec3(0.0f, -2.0f, 0.0f));
    waterObject->AddComponent(new MeshRenderer(highPolyPlane->GetMesh(0), waterMaterial));
    scene.AddGameObject(waterObject);

    // Setup physics debug
    Physics::SetDebugRendererMaterial(physicsMaterial);
    Physics::ToggleDebugWireframe();
}

void GraphicDemoApplication::CustomRun()
{
    // Toggle physics debug wireframe (this causes memory to accumulate each time it's done)
    // TODO: Fix memory leak
    if (Input::GetKeyPressed(GLFW_KEY_P)) { Physics::ToggleDebugWireframe(); }

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

    // Close window if escape key is pressed
    if (Input::GetKeyPressed(GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(Application::_window.GetGlWindow(), true); }

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
    rainbowLightObject->GetTransform()->SetLocalPosition(glm::vec3(sin(Time::GetTimeSinceStart()) * 5.0f, 0.0f, 0.0f));
    redLightObject->GetTransform()->SetLocalPosition(glm::vec3(0.0, 0.0f, sin(Time::GetTimeSinceStart()) * 5.0f));

    // Move crate
    crateObject->GetComponent<Rigidbody>()->ApplyForce(crateVelocity * 100.0f);
    crateObject->GetComponent<Rigidbody>()->ApplyTorque(crateVelocity * 100.0f);


    if (Input::GetKeyPressed(GLFW_KEY_0))
    {
        childCrateObject->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    
    GameEngine::Debug::Log::Message("crate world pos: " + glm::to_string(crateObject->GetTransform()->GetPosition()));
    GameEngine::Debug::Log::Message("crate local pos: " + glm::to_string(crateObject->GetTransform()->GetLocalPosition()));

    GameEngine::Debug::Log::Message("crate child world pos: " + glm::to_string(childCrateObject->GetTransform()->GetPosition()));
    GameEngine::Debug::Log::Message("crate child local pos: " + glm::to_string(childCrateObject->GetTransform()->GetLocalPosition()));

    GameEngine::Debug::Log::Message("crate child child world pos: " + glm::to_string(childOfChildCrateObject->GetTransform()->GetPosition()));
    GameEngine::Debug::Log::Message("crate child child local pos: " + glm::to_string(childOfChildCrateObject->GetTransform()->GetLocalPosition()));
    
    // Move camera
    cameraObject->GetTransform()->Move(cameraVelocity);
}
