#include "GraphicDemoApplication.h"

#include <reactphysics3d/reactphysics3d.h>

#include <glm/ext/quaternion_common.hpp>

#include "tiny_gltf.h"
#include "GameEngine//Components/BoxCollider.h"
#include "GameEngine//Components/Camera.h"
#include "GameEngine//Components/MeshRenderer.h"
#include "GameEngine//Components/PointLight.h"
#include "GameEngine//Components/Rigidbody.h"
#include "GameEngine//Components/TransformComponent.h"
#include "GameEngine//Core/Window.h"
#include "GameEngine//Input/Input.h"
#include "GameEngine//Physics/Physics.h"
#include "GameEngine//Rendering/Material.h"
#include "GameEngine//Rendering/Model.h"
#include "GameEngine//Rendering/Renderer.h"
#include "GameEngine//Rendering/Shader.h"
#include "GameEngine//Rendering/Texture.h"
#include "GameEngine//Utils/Math.h"
#include "GameEngine/Utils/Time.h"

using namespace GameEngine::Debug;
using namespace GameEngine::Utils;
using namespace GameEngine::Core;
using namespace GameEngine::Rendering;
using namespace GameEngine::Components;
using namespace GameEngine::Physics;
using namespace GameEngine::Input;

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

Shader* defaultShader;
Shader* physicsDebugShader;

Material* dudeMaterial;
Material* crateMaterial;
Material* physicsMaterial;

GameObject* cameraObject;
GameObject* redLightObject;
GameObject* rainbowLightObject;
GameObject* suzanneObject;
GameObject* cubeObject;
GameObject* crateObject;

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

    defaultShader = new Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");

    // Matrices
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

    dudeMaterial = new Material(defaultShader);
    dudeMaterial->GetUniformBuffer()->SetUniform("u_Texture", theDudeTexture);

    crateMaterial = new Material(defaultShader);
    crateMaterial->GetUniformBuffer()->SetUniform("u_Texture", crateTexture);
    crateMaterial->GetUniformBuffer()->SetUniform("u_NormalMap", crateNormalMapTexture);
    crateMaterial->GetUniformBuffer()->SetUniform("u_NormalMapIntensity", 0.01f);

    // Physics Debug
    physicsDebugShader = new Shader("res/shaders/PhysicsDebugShader.vsh", "res/shaders/PhysicsDebugShader.fsh");
    physicsDebugShader->InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);

    physicsMaterial = new Material(physicsDebugShader);
    physicsMaterial->SetCullFace(Material::None);
    physicsMaterial->SetRenderMode(Material::Wireframe);

    // Camera
    cameraObject    = new GameObject();
    Transform*  cameraTransform = cameraObject->GetTransform();
    cameraTransform->SetPosition(glm::vec3(0.0f, 0.0f, 8.0f));
    cameraObject->AddComponent(new Camera(60, 0.01f, 100.0f));
    scene.AddGameObject(cameraObject);

    // Red Light
    redLightObject    = new GameObject();
    Transform*  redLightTransform = redLightObject->GetTransform();
    redLightTransform->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    redLightTransform->SetScale(glm::vec3(0.1f));
    redLightObject->AddComponent(new MeshRenderer(sphereModel->GetMesh(0), dudeMaterial));
    redLightObject->AddComponent(new PointLight(defaultShader, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 2.0f));
    scene.AddGameObject(redLightObject);

    // Rainbow Light
    rainbowLightObject    = new GameObject();
    Transform*  rainbowLightTransform = rainbowLightObject->GetTransform();
    rainbowLightTransform->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
    rainbowLightTransform->SetScale(glm::vec3(0.1f));
    rainbowLightObject->AddComponent(new MeshRenderer(sphereModel->GetMesh(0), dudeMaterial));
    rainbowLightObject->AddComponent(new PointLight(defaultShader, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 2.0f));
    scene.AddGameObject(rainbowLightObject);

    // Suzanne
    suzanneObject    = new GameObject();
    Transform*  suzanneTransform = suzanneObject->GetTransform();
    suzanneObject->AddComponent(new MeshRenderer(suzanneModel->GetMesh(0), dudeMaterial));
    suzanneTransform->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
    scene.AddGameObject(suzanneObject);

    // The Missing
    cubeObject    = new GameObject();
    cubeObject->AddComponent(new MeshRenderer(theMissingModel->GetMesh(0), {dudeMaterial, crateMaterial}, 2));
    cubeObject->AddComponent(new MeshRenderer(theMissingModel->GetMesh(1), dudeMaterial));
    cubeObject->AddComponent(new MeshRenderer(theMissingModel->GetMesh(2), dudeMaterial));
    scene.AddGameObject(cubeObject);

    // Crate
    crateObject    = new GameObject();
    Transform*  crateTransform = crateObject->GetTransform();
    crateTransform->SetPosition(glm::vec3(0.0f, 4.0f, 0.0f));
    crateObject->AddComponent(new MeshRenderer(cubeModel->GetMesh(0), crateMaterial));
    crateObject->AddComponent(new BoxCollider(glm::vec3(0.5f)));
    crateObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::DYNAMIC));
    scene.AddGameObject(crateObject);

    // Floor
    GameObject* floorObject    = new GameObject();
    Transform*  floorTransform = floorObject->GetTransform();
    floorTransform->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
    floorTransform->SetScale(glm::vec3(5.0f, 1.0f, 5.0f));
    floorObject->AddComponent(new MeshRenderer(cubeModel->GetMesh(0), crateMaterial));
    floorObject->AddComponent(new BoxCollider(glm::vec3(2.5f, 0.5f, 2.5f)));
    floorObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::STATIC));
    scene.AddGameObject(floorObject);
    
    Physics::SetDebugRendererMaterial(physicsMaterial);
    Physics::ToggleDebugWireframe();
}

void GraphicDemoApplication::CustomRun()
{
    if (Input::GetKeyPressed(GLFW_KEY_P)) { Physics::ToggleDebugWireframe(); }

    glm::vec4 wasdVelocity = glm::vec4(0.0f);
    if (Input::GetKeyDown(GLFW_KEY_D)) { wasdVelocity.x += 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_A)) { wasdVelocity.x -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_W)) { wasdVelocity.z -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_S)) { wasdVelocity.z += 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_LEFT_SHIFT)) { wasdVelocity.y -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_SPACE)) { wasdVelocity.y += 5.0f * Time::GetDeltaTime(); }

    glm::vec4 arrowVelocity = glm::vec4(0.0f);
    if (Input::GetKeyDown(GLFW_KEY_RIGHT)) { arrowVelocity.x += 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_LEFT)) { arrowVelocity.x -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_UP)) { arrowVelocity.z -= 5.0f * Time::GetDeltaTime(); }
    if (Input::GetKeyDown(GLFW_KEY_DOWN)) { arrowVelocity.z += 5.0f * Time::GetDeltaTime(); }

    // Close window if escape key is pressed
    if (Input::GetKeyPressed(GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(Application::_window.GetGlWindow(), true); }

    rainbowLightObject->GetComponent<PointLight>()->SetColor(glm::vec4(
                                                                       Math::Sin01(Time::GetTimeSinceStart() + 250),
                                                                       Math::Sin01(Time::GetTimeSinceStart() + 500),
                                                                       Math::Sin01(Time::GetTimeSinceStart() + 750),
                                                                       1.0f
                                                                      ));

    cubeObject->GetTransform()->Rotate(glm::vec3(0.0f, 0.0f, 45.0f * Time::GetDeltaTime()));
    suzanneObject->GetTransform()->Rotate(glm::vec3(0.0f, 45.0f * Time::GetDeltaTime(), 0.0f));

    crateObject->GetComponent<Rigidbody>()->ApplyForce(arrowVelocity * 100.0f);

    rainbowLightObject->GetTransform()->SetPosition(glm::vec3(sin(Time::GetTimeSinceStart()) * 5.0f, 1.0f, 0.0f));
    redLightObject->GetTransform()->SetPosition(glm::vec3(0.0, 0.0f, sin(Time::GetTimeSinceStart()) * 5.0f));

    cameraObject->GetTransform()->Move(wasdVelocity);
}
