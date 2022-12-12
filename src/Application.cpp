#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_common.hpp>

#include "Components/CameraComponent.h"
#include "Components/MeshRendererComponent.h"
#include "Core/Window.h"
#include "Components/TransformComponent.h"
#include "Core/Scene.h"
#include "Input/Input.h"
#include "Rendering/Material.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Shapes/Cube.h"
#include "Utils/Math.h"
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

    Shader defaultShader = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");

    Material defaultMaterial = Material(&defaultShader);

    // Camera
    GameObject      cameraObject    = GameObject();
    CameraComponent cameraComponent = CameraComponent(60, 0.01f, 1000.0f);
    Transform&      cameraTransform = cameraObject.GetTransform();
    cameraTransform.SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    cameraObject.AddComponent(&cameraComponent);
    scene.AddGameObject(cameraObject);

    // Cube
    GameObject            cubeObject       = GameObject();
    Cube                  cube             = Cube();
    MeshRendererComponent cubeMeshRenderer = MeshRendererComponent(cube.GetMesh(), &defaultMaterial);
    Transform&            cubeTransform    = cubeObject.GetTransform();
    cubeObject.AddComponent(&cubeMeshRenderer);
    scene.AddGameObject(cubeObject);

    // Floor
    GameObject            floorObject       = GameObject();
    Cube                  floorCube         = Cube();
    MeshRendererComponent floorMeshRenderer = MeshRendererComponent(floorCube.GetMesh(), &defaultMaterial);
    Transform&            floorTransform    = floorObject.GetTransform();
    floorObject.AddComponent(&floorMeshRenderer);
    floorTransform.SetPosition(glm::vec3(0.0f, -30.0f, 0.0f));
    floorTransform.SetScale(glm::vec3(20.0f));
    scene.AddGameObject(floorObject);

    scene.InitializeScene();

    while (!_window.ShouldClose())
    {
        Input::Update();

        Time::UpdateDeltaTime();

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
        
        if (Input::GetKeyPressed(GLFW_KEY_0)) { std::cout << "0" << std::endl; }
        if (Input::GetKeyPressed(GLFW_KEY_1)) { std::cout << "1" << std::endl; }
        if (Input::GetKeyPressed(GLFW_KEY_2)) { std::cout << "2" << std::endl; }
        if (Input::GetKeyPressed(GLFW_KEY_3)) { std::cout << "3" << std::endl; }



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
        
        velocity = cameraObject.GetTransform().GetTRS() * velocity;

        cameraComponent.SetFOVInDegrees(Math::Lerp(45.0f, 90.0f, Math::Sin01(Time::GetTimeSinceStart())));

        cubeTransform.Rotate(glm::vec3(0.0f, 0.0f, 45.0f * Time::GetDeltaTime()));

        cameraTransform.Move(velocity);
        cameraTransform.Rotate(look);

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
