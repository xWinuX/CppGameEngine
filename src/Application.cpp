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
#include "Physics/PhysicsManager.h"
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

    Model cubeModel       = Model("res/models/Cube.obj");
    Model cubeGLTFModel   = Model("res/models/cube.gltf");
    Model suzanneModel    = Model("res/models/Suzanne.obj");
    Model theMissingModel = Model("res/models/TheMissing.obj");
    Model sphereModel     = Model("res/models/Sphere.obj");

    Shader defaultShader = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");
    // Matrices
    defaultShader.InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);
    defaultShader.InitializeUniform<glm::mat4>("u_Transform", glm::identity<glm::mat4>(), false);

    // Lighting
    defaultShader.InitializeUniform<int>("u_NumPointLights", 0, false);
    defaultShader.InitializeUniform<std::vector<glm::vec3>*>("u_PointLightPositions", nullptr, false);
    defaultShader.InitializeUniform<std::vector<glm::vec4>*>("u_PointLightColors", nullptr, false);
    defaultShader.InitializeUniform<std::vector<float>*>("u_PointLightIntensities", nullptr, false);
    defaultShader.InitializeUniform<std::vector<float>*>("u_PointLightRanges", nullptr, false);

    // Other
    defaultShader.InitializeUniform<glm::vec4>("u_ColorTint", glm::vec4(1.0f));
    defaultShader.InitializeUniform<Texture*>("u_Texture", noTexture);
    defaultShader.InitializeUniform<Texture*>("u_NormalMap", crateNormalMapTexture);
    defaultShader.InitializeUniform<float>("u_NormalMapIntensity", 1.0f);

    Material defaultMaterial = Material(&defaultShader);

    defaultMaterial.GetUniformBuffer()->SetUniform("u_Texture", crateTexture);
    //defaultMaterial.SetUniformTextureSampler2D("u_Texture", &theDudeTexture);


    Material redMaterial = Material(&defaultShader);

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
    GameObject* redLightObject = new GameObject();
    Transform*  redLight       = redLightObject->GetTransform();
    redLight->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    redLight->SetScale(glm::vec3(0.1f));
    redLightObject->AddComponent(new MeshRenderer(sphereModel.GetMesh(0), &defaultMaterial));
    redLightObject->AddComponent(new PointLight(&defaultShader, glm::vec4(1.0f, 0.0f, 0.0f, -5.0f)));
    scene.AddGameObject(redLightObject);

    // Rainbow Light
    GameObject* rainbowLightObject = new GameObject();
    Transform*  rainbowLight       = rainbowLightObject->GetTransform();
    rainbowLight->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
    rainbowLight->SetScale(glm::vec3(0.1f));
    rainbowLightObject->AddComponent(new MeshRenderer(sphereModel.GetMesh(0), &defaultMaterial));
    rainbowLightObject->AddComponent(new PointLight(&defaultShader, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 2.0f));
    scene.AddGameObject(rainbowLightObject);

    // Suzanne
    GameObject* suzanneObject    = new GameObject();
    Transform*  suzanneTransform = suzanneObject->GetTransform();
    suzanneObject->AddComponent(new MeshRenderer(suzanneModel.GetMesh(0), &redMaterial));
    suzanneTransform->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
    scene.AddGameObject(suzanneObject);

    // The Missing
    GameObject* cubeObject    = new GameObject();
    Transform*  cubeTransform = cubeObject->GetTransform();
    cubeObject->AddComponent(new MeshRenderer(theMissingModel.GetMesh(0), &defaultMaterial));
    cubeObject->AddComponent(new MeshRenderer(theMissingModel.GetMesh(1), &defaultMaterial));
    cubeObject->AddComponent(new MeshRenderer(theMissingModel.GetMesh(2), &defaultMaterial));
    scene.AddGameObject(cubeObject);

    // Crate
    GameObject* crateObject    = new GameObject();
    Transform*  crateTransform = crateObject->GetTransform();
    crateTransform->SetPosition(glm::vec3(0.0f, 4.0f, 0.0f));
    crateObject->AddComponent(new MeshRenderer(cubeGLTFModel.GetMesh(0), &defaultMaterial));
    crateObject->AddComponent(new BoxCollider(glm::vec3(0.5f)));
    crateObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::DYNAMIC));
    scene.AddGameObject(crateObject);

    // Floor
    GameObject* floorObject    = new GameObject();
    Transform*  floorTransform = floorObject->GetTransform();
    floorTransform->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
    floorTransform->SetScale(glm::vec3(5.0f, 1.0f, 5.0f));
    floorObject->AddComponent(new MeshRenderer(cubeGLTFModel.GetMesh(0), &defaultMaterial));
    floorObject->AddComponent(new BoxCollider(glm::vec3(2.5f, 0.5f, 2.5f)));
    floorObject->AddComponent(new Rigidbody(reactphysics3d::BodyType::STATIC));
    scene.AddGameObject(floorObject);

    scene.InitializeScene();

    PhysicsManager::SetDebugRendererMaterial(&physicsMaterial);
    PhysicsManager::ToggleDebugWireframe();
    
    while (!_window.ShouldClose())
    {
        // Update delta time
        Time::Update();

        // Update the new input state
        Input::Update();


        if (Input::GetKeyPressed(GLFW_KEY_P))
        {
            PhysicsManager::ToggleDebugWireframe();
        }
        
        // Execute the physics update on all objects if needed
        PhysicsManager::Update(&scene);
        
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

        //crateTransform->SetEulerAngles(glm::vec3(Time::GetTimeSinceStart() * 10.0f));

        
        cubeTransform->Rotate(glm::vec3(0.0f, 0.0f, 45.0f * Time::GetDeltaTime()));
        suzanneTransform->Rotate(glm::vec3(0.0f, 45.0f * Time::GetDeltaTime(), 0.0f));

        crateObject->GetComponent<Rigidbody>()->ApplyForce(arrowVelocity*100.0f);

        rainbowLight->SetPosition(glm::vec3(Math::Sin01(Time::GetTimeSinceStart()) * 5.0f, 1.0f, 0.0f));
        
        //floorTransform->GetPhysicsTransform().setPosition(floorTransform->GetPhysicsTransform().getPosition() + reactphysics3d::Vector3(arrowVelocity.x, arrowVelocity.y, arrowVelocity.z));
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
