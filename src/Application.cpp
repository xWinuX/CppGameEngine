#include <reactphysics3d/reactphysics3d.h>
#include "Application.h"

#include <glm/ext/quaternion_common.hpp>

#include "tiny_gltf.h"
#include "Components/BoxCollider.h"
#include "Components/Camera.h"
#include "Components/MeshRenderer.h"
#include "Components/PointLight.h"
#include "Components/Rigidbody.h"
#include "Components/TransformComponent.h"
#include "Core/Scene.h"
#include "Core/Window.h"
#include "Input/Input.h"
#include "Physics/Physics.h"
#include "Rendering/Material.h"
#include "Rendering/Model.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Utils/Math.h"
#include "Utils/Time.h"

using namespace GameEngine::Core;
using namespace GameEngine::Rendering;
using namespace GameEngine::Components;
using namespace GameEngine::Physics;
using namespace GameEngine::Input;

Window Application::_window = Window(glm::ivec2(800, 600));

bool cull = false;

Application::Application()
{
    glfwInit();

    _window.CreateContext();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) { Debug::Log::Error("Failed to initialize GLAD"); }

    Renderer::Initialize();
}

void Application::Run() const
{
    Scene scene = Scene();

    Texture* noTexture               = new Texture("res/textures/NoTexture.png");
    Texture* blackTexture            = new Texture("res/textures/Black.png");
    Texture* whiteTexture            = new Texture("res/textures/White.png");
    Texture* normalMapDefaultTexture = new Texture("res/textures/NormalMapDefault.png");
    Texture* theDudeTexture          = new Texture("res/textures/TheDude.png");
    Texture* crateTexture            = new Texture("res/textures/Crate.jpg");
    Texture* crateNormalMapTexture   = new Texture("res/textures/CrateNormalMap.png");

    Model cubeModel       = Model("res/models/Cube.gltf");
    Model suzanneModel    = Model("res/models/Suzanne.gltf");
    Model theMissingModel = Model("res/models/TheMissing.gltf");
    Model sphereModel     = Model("res/models/Sphere.gltf");

    Shader defaultShader = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");

    // Matrices
    defaultShader.InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);
    defaultShader.InitializeUniform<glm::mat4>("u_Transform", glm::identity<glm::mat4>(), false);

    // Lighting
    defaultShader.InitializeUniform<glm::vec4>("u_AmbientLightColor", glm::vec4(1.0));
    defaultShader.InitializeUniform<float>("u_AmbientLightIntensity", 0.5f);

    defaultShader.InitializeUniform<int>("u_NumPointLights", 0, false);
    defaultShader.InitializeUniform<std::vector<glm::vec3>*>("u_PointLightPositions", nullptr, false);
    defaultShader.InitializeUniform<std::vector<glm::vec4>*>("u_PointLightColors", nullptr, false);
    defaultShader.InitializeUniform<std::vector<float>*>("u_PointLightIntensities", nullptr, false);
    defaultShader.InitializeUniform<std::vector<float>*>("u_PointLightRanges", nullptr, false);

    // Other
    defaultShader.InitializeUniform<glm::vec4>("u_ColorTint", glm::vec4(1.0f));
    defaultShader.InitializeUniform<Texture*>("u_Texture", noTexture);
    defaultShader.InitializeUniform<Texture*>("u_NormalMap", normalMapDefaultTexture);
    defaultShader.InitializeUniform<float>("u_NormalMapIntensity", 1.0f);

    Material dudeMaterial = Material(&defaultShader);
    dudeMaterial.GetUniformBuffer()->SetUniform("u_Texture", theDudeTexture);

    Material crateMaterial = Material(&defaultShader);
    crateMaterial.GetUniformBuffer()->SetUniform("u_Texture", crateTexture);
    crateMaterial.GetUniformBuffer()->SetUniform("u_NormalMap", crateNormalMapTexture);
    crateMaterial.GetUniformBuffer()->SetUniform("u_NormalMapIntensity", 0.01f);

    // Physics Debug
    Shader physicsDebugShader = Shader("res/shaders/PhysicsDebugShader.vsh", "res/shaders/PhysicsDebugShader.fsh");
    physicsDebugShader.InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);

    Material physicsMaterial = Material(&physicsDebugShader);
    physicsMaterial.SetCullFace(Material::None);
    physicsMaterial.SetRenderMode(Material::Wireframe);

    // Camera
    GameObject* cameraObject    = new GameObject();
    Transform*  cameraTransform = cameraObject->GetTransform();
    cameraTransform->SetPosition(glm::vec3(0.0f, 0.0f, 8.0f));
    cameraObject->AddComponent(new Camera(60, 0.01f, 100.0f));
    scene.AddGameObject(cameraObject);

    // Red Light
    GameObject* redLightObject    = new GameObject();
    Transform*  redLightTransform = redLightObject->GetTransform();
    redLightTransform->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    redLightTransform->SetScale(glm::vec3(0.1f));
    redLightObject->AddComponent(new MeshRenderer(sphereModel.GetMesh(0), &dudeMaterial));
    redLightObject->AddComponent(new PointLight(&defaultShader, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 2.0f));
    scene.AddGameObject(redLightObject);

    // Rainbow Light
    GameObject* rainbowLightObject    = new GameObject();
    Transform*  rainbowLightTransform = rainbowLightObject->GetTransform();
    rainbowLightTransform->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
    rainbowLightTransform->SetScale(glm::vec3(0.1f));
    rainbowLightObject->AddComponent(new MeshRenderer(sphereModel.GetMesh(0), &dudeMaterial));
    rainbowLightObject->AddComponent(new PointLight(&defaultShader, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 2.0f));
    scene.AddGameObject(rainbowLightObject);

    // Suzanne
    GameObject* suzanneObject    = new GameObject();
    Transform*  suzanneTransform = suzanneObject->GetTransform();
    suzanneObject->AddComponent(new MeshRenderer(suzanneModel.GetMesh(0), &dudeMaterial));
    suzanneTransform->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
    scene.AddGameObject(suzanneObject);

    // The Missing
    GameObject* cubeObject    = new GameObject();
    Transform*  cubeTransform = cubeObject->GetTransform();
    cubeObject->AddComponent(new MeshRenderer(theMissingModel.GetMesh(0), {&dudeMaterial, &crateMaterial}, 2));
    cubeObject->AddComponent(new MeshRenderer(theMissingModel.GetMesh(1), &dudeMaterial));
    cubeObject->AddComponent(new MeshRenderer(theMissingModel.GetMesh(2), &dudeMaterial));
    scene.AddGameObject(cubeObject);

    // Crate
    GameObject* crateObject    = new GameObject();
    Transform*  crateTransform = crateObject->GetTransform();
    crateTransform->SetPosition(glm::vec3(0.0f, 4.0f, 0.0f));
    crateObject->AddComponent(new MeshRenderer(cubeModel.GetMesh(0), &crateMaterial));
    crateObject->AddComponent(new BoxCollider(glm::vec3(0.5f)));
    crateObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::DYNAMIC));
    scene.AddGameObject(crateObject);

    // Floor
    GameObject* floorObject    = new GameObject();
    Transform*  floorTransform = floorObject->GetTransform();
    floorTransform->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
    floorTransform->SetScale(glm::vec3(5.0f, 1.0f, 5.0f));
    floorObject->AddComponent(new MeshRenderer(cubeModel.GetMesh(0), &crateMaterial));
    floorObject->AddComponent(new BoxCollider(glm::vec3(2.5f, 0.5f, 2.5f)));
    floorObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::STATIC));
    scene.AddGameObject(floorObject);

    scene.InitializeScene();

    Physics::SetDebugRendererMaterial(&physicsMaterial);
    Physics::ToggleDebugWireframe();

    while (!_window.ShouldClose())
    {
        // Update delta time
        Time::Update();

        // Update the new input state
        Input::Update();

        if (Input::GetKeyPressed(GLFW_KEY_P)) { Physics::ToggleDebugWireframe(); }

        // Execute the physics update on all objects if needed
        Physics::Update(&scene);

        // Execute Update calls on each game object in the current scene
        scene.Update();

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
        if (Input::GetKeyPressed(GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(_window.GetGlWindow(), true); }

        // Enable/Disable culling
        if (Input::GetKeyPressed(GLFW_KEY_C))
        {
            cull = !cull;
            if (cull) { glEnable(GL_CULL_FACE); }
            else { glDisable(GL_CULL_FACE); }
        }

        rainbowLightObject->GetComponent<PointLight>()->SetColor(glm::vec4(
                                                                           Math::Sin01(Time::GetTimeSinceStart() + 250),
                                                                           Math::Sin01(Time::GetTimeSinceStart() + 500),
                                                                           Math::Sin01(Time::GetTimeSinceStart() + 750),
                                                                           1.0f
                                                                          ));

        cubeTransform->Rotate(glm::vec3(0.0f, 0.0f, 45.0f * Time::GetDeltaTime()));
        suzanneTransform->Rotate(glm::vec3(0.0f, 45.0f * Time::GetDeltaTime(), 0.0f));

        crateObject->GetComponent<Rigidbody>()->ApplyForce(arrowVelocity * 100.0f);

        rainbowLightTransform->SetPosition(glm::vec3(sin(Time::GetTimeSinceStart()) * 5.0f, 1.0f, 0.0f));
        redLightTransform->SetPosition(glm::vec3(0.0, 0.0f, sin(Time::GetTimeSinceStart()) * 5.0f));

        cameraTransform->Move(wasdVelocity);

        // Render
        Renderer::Draw();
    }

    // Cleanup textures
    delete noTexture;
    delete blackTexture;
    delete normalMapDefaultTexture;
    delete whiteTexture;
    delete theDudeTexture;
    delete crateTexture;
    delete crateNormalMapTexture;

    //------------------------------
    // glfw: terminate, clearing all previously allocated GLFW resources.
    //------------------------------
    glfwTerminate();
}
