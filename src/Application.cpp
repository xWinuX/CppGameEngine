#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include <glm/ext/matrix_transform.hpp>
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

    Texture theDudeTexture = Texture("res/textures/TheDude.png");
    theDudeTexture.Bind(0);
    
    Shader defaultShader = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");
    defaultShader.InitializeUniform("u_Texture");

    Material defaultMaterial = Material(&defaultShader);
    defaultMaterial.SetUniformTextureSampler2D("u_Texture", &theDudeTexture);

    Model model = Model("res/models/Cube.obj");
    
    // Camera
    GameObject* cameraObject = new GameObject();
    Transform* cameraTransform = cameraObject->GetTransform();
    cameraTransform->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    cameraObject->AddComponent(new Camera(60, 0.01f, 100.0f));
    scene.AddGameObject(cameraObject);

    // Cube
    GameObject* cubeObject = new GameObject();
    Cube        cube       = Cube();
    Transform* cubeTransform = cubeObject->GetTransform();
    cubeObject->AddComponent(new MeshRenderer(cube.GetMesh(), &defaultMaterial));
    scene.AddGameObject(cubeObject);

    // Floor
    GameObject* floorObject    = new GameObject();
    Cube        floorCube      = Cube();
    Transform*  floorTransform = floorObject->GetTransform();
    floorObject->AddComponent(new MeshRenderer(floorCube.GetMesh(), &defaultMaterial));
    floorTransform->SetPosition(glm::vec3(0.0f, -30.0f, 0.0f));
    floorTransform->SetScale(glm::vec3(20.0f));
    scene.AddGameObject(floorObject);

    scene.InitializeScene();

    while (!_window.ShouldClose())
    {
        // Update engine internal systems
        Input::Update();
        Time::Update();

        //------------------------------
        // Gameplay
        //------------------------------
        scene.Update();

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

        //------------------------------
        // Render
        //------------------------------
        Renderer::Draw();
    }

    //------------------------------
    // glfw: terminate, clearing all previously allocated GLFW resources.
    //------------------------------
    glfwTerminate();
}
