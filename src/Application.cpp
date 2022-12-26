#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include <glm/ext/quaternion_common.hpp>
#include "Components/Camera.h"
#include "Components/MeshRenderer.h"
#include "Core/Window.h"
#include "Components/TransformComponent.h"
#include "Core/Scene.h"
#include "Input/Input.h"
#include "Rendering/Material.h"
#include "Rendering/Model.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Shapes/Cube.h"
#include "Utils/Time.h"

#define INITIAL_WINDOW_WIDTH  800
#define INITIAL_WINDOW_HEIGHT 600

Window Application::_window = Window(glm::ivec2(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT));

bool cull = false;

Application::Application()
{
    glfwInit();

    _window.CreateContext();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) { std::cout << "Failed to initialize GLAD" << std::endl; }

    Renderer::Initialize();
}

void Application::Run() const
{
    Scene scene = Scene();

    Texture* theDudeTexture = new Texture("res/textures/TheDude.png");
    Texture* createTexture =  new Texture("res/textures/Crate.jpg");
    
    auto defaultShader = new Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");
    
    defaultShader->InitializeUniform<glm::mat4>("u_ViewProjection", glm::identity<glm::mat4>(), false);
    defaultShader->InitializeUniform<glm::mat4>("u_Transform", glm::identity<glm::mat4>(), false);
    
    defaultShader->InitializeUniform<glm::vec4>("u_ColorTint", glm::vec4(1.0f));
    defaultShader->InitializeUniform<Texture*>("u_Texture", nullptr);
    
    Material defaultMaterial = Material(defaultShader);
    
    defaultMaterial.GetUniformBuffer()->SetUniform("u_Texture", theDudeTexture);
    //defaultMaterial.SetUniformTextureSampler2D("u_Texture", &theDudeTexture);

    Material redMaterial = Material(defaultShader);
    redMaterial.GetUniformBuffer()->SetUniform("u_Texture", theDudeTexture);
    
    Material crateMaterial = Material(defaultShader);
    crateMaterial.GetUniformBuffer()->SetUniform("u_Texture", createTexture);
    
    Model cubeModel = Model("res/models/Cube.obj");
    Model suzanneModel = Model("res/models/Suzanne.obj");
    Model theMissingModel = Model("res/models/TheMissing.obj");
    
    // Camera
    GameObject* cameraObject = new GameObject();
    Transform* cameraTransform = cameraObject->GetTransform();
    cameraTransform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    cameraObject->AddComponent(new Camera(60, 0.01f, 100.0f));
    scene.AddGameObject(cameraObject);

    // Suzanne
    GameObject* suzanneObject = new GameObject();
    Transform* suzanneTransform = suzanneObject->GetTransform();
    suzanneObject->AddComponent(new MeshRenderer(suzanneModel.GetMesh(0), &redMaterial));
    suzanneTransform->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
    scene.AddGameObject(suzanneObject);
    
    // The Missing
    GameObject* cubeObject = new GameObject();
    Transform* cubeTransform = cubeObject->GetTransform();
    cubeObject->AddComponent(new MeshRenderer(theMissingModel.GetMesh(0), &defaultMaterial));
    cubeObject->AddComponent(new MeshRenderer(theMissingModel.GetMesh(1), &defaultMaterial));
    cubeObject->AddComponent(new MeshRenderer(theMissingModel.GetMesh(2), &defaultMaterial));
    scene.AddGameObject(cubeObject);

    // Floor
    GameObject* floorObject    = new GameObject();
    Transform*  floorTransform = floorObject->GetTransform();
    floorObject->AddComponent(new MeshRenderer(cubeModel.GetMesh(0), &crateMaterial));
    floorTransform->SetPosition(glm::vec3(0.0f, -30.0f, 0.0f));
    floorTransform->SetScale(glm::vec3(20.0f));
    scene.AddGameObject(floorObject);

    scene.InitializeScene();

    while (!_window.ShouldClose())
    {
        // Update engine internal systems
        Input::Update();
        Time::Update();
        
        // Gameplay
        scene.Update();

        if (Input::GetKeyPressed(GLFW_KEY_0))
        {
            MeshRenderer* meshRenderer = suzanneObject->GetComponent<MeshRenderer>();
            meshRenderer->SetVisible(!meshRenderer->GetVisible());
        }
        
        glm::vec4 velocity = glm::vec4(0.0f);
        if (Input::GetKeyDown(GLFW_KEY_SPACE)) { velocity.y += 5.0f * Time::GetDeltaTime(); }
        if (Input::GetKeyDown(GLFW_KEY_LEFT_SHIFT)) { velocity.y -= 5.0f * Time::GetDeltaTime(); }
        if (Input::GetKeyDown(GLFW_KEY_D)) { velocity.x += 5.0f * Time::GetDeltaTime(); }
        if (Input::GetKeyDown(GLFW_KEY_A)) { velocity.x -= 5.0f * Time::GetDeltaTime(); }
        if (Input::GetKeyDown(GLFW_KEY_W)) { velocity.z -= 5.0f * Time::GetDeltaTime(); }
        if (Input::GetKeyDown(GLFW_KEY_S)) { velocity.z += 5.0f * Time::GetDeltaTime(); }

        glm::vec4 look = glm::vec4(0.0f);
        if (Input::GetKeyDown(GLFW_KEY_RIGHT)) { look.y -= 50.0f * Time::GetDeltaTime(); }
        if (Input::GetKeyDown(GLFW_KEY_LEFT)) { look.y += 50.0f * Time::GetDeltaTime(); }
        if (Input::GetKeyDown(GLFW_KEY_UP)) { look.x -= 50.0f * Time::GetDeltaTime(); }
        if (Input::GetKeyDown(GLFW_KEY_DOWN)) { look.x += 50.0f * Time::GetDeltaTime(); }

        // Close window if escape key is pressed
        if (Input::GetKeyPressed(GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(_window.GetGlWindow(), true); }

        // Change polygon Mode
        if (Input::GetKeyPressed(GLFW_KEY_P)) { glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); }
        if (Input::GetKeyPressed(GLFW_KEY_F)) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
        if (Input::GetKeyPressed(GLFW_KEY_L)) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

        // Enable/Disable culling
        if (Input::GetKeyPressed(GLFW_KEY_C))
        {
            cull = !cull;
            if (cull) { glEnable(GL_CULL_FACE); }
            else { glDisable(GL_CULL_FACE); }
        }
        
        velocity = cameraObject->GetTransform()->GetTRS() * velocity;

        cubeTransform->Rotate(glm::vec3(0.0f, 0.0f, 45.0f * Time::GetDeltaTime()));

        cameraTransform->Move(velocity);
        cameraTransform->Rotate(look);

        // Render
        Renderer::Draw();
    }

    delete theDudeTexture;
    delete createTexture;
    
    //------------------------------
    // glfw: terminate, clearing all previously allocated GLFW resources.
    //------------------------------
    glfwTerminate();
}
