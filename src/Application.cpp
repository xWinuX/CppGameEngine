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
#include "Rendering/Material.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Shapes/Cube.h"
#include "Utils/Math.h"

#define INITIAL_WINDOW_WIDTH  800
#define INITIAL_WINDOW_HEIGHT 600

Window Application::_window = Window(glm::ivec2(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT));

bool cull = false;

void keyCallback(GLFWwindow* window, const int key, int scancode, const int action, int mods)
{
    // Close window if escape key is pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }

    // Change polygon Mode
    if (key == GLFW_KEY_P && action == GLFW_PRESS) { glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); }
    if (key == GLFW_KEY_F && action == GLFW_PRESS) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
    if (key == GLFW_KEY_L && action == GLFW_PRESS) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

    // Enable/Disable culling
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        cull = !cull;
        if (cull) { glEnable(GL_CULL_FACE); }
        else { glDisable(GL_CULL_FACE); }
    }
}

float getCurrentTime() { return static_cast<float>(glfwGetTime()); }

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

    // Set Callbacks
    glfwSetKeyCallback(_window.GetGlWindow(), keyCallback);

    scene.InitializeScene();

    float currentTime = getCurrentTime();
    while (!glfwWindowShouldClose(_window.GetGlWindow()))
    {
        //------------------------------
        // Time
        //------------------------------
        const float newTime   = getCurrentTime();
        float       deltaTime = newTime - currentTime;
        currentTime           = newTime;
        
        //------------------------------
        // Gameplay
        //------------------------------
        scene.Update();

        glm::vec4 velocity = glm::vec4(0.0f);
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) { velocity.y += 5.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { velocity.y -= 5.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_D) == GLFW_PRESS) { velocity.x += 5.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_A) == GLFW_PRESS) { velocity.x -= 5.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_W) == GLFW_PRESS) { velocity.z -= 5.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_S) == GLFW_PRESS) { velocity.z += 5.0f * deltaTime; }

        glm::vec4 look = glm::vec4(0.0f);
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) { look.y -= 50.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) { look.y += 50.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_UP) == GLFW_PRESS) { look.x -= 50.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) { look.x += 50.0f * deltaTime; }

        velocity = cameraObject.GetTransform().GetTRS() * velocity;

        cameraComponent.SetFOVInDegrees(Math::Lerp(45.0f, 90.0f, Math::Sin01(currentTime)));

        cubeTransform.Rotate(glm::vec3(0.0f, 0.0f, 45.0f * deltaTime));

        cameraTransform.Move(velocity);
        cameraTransform.Rotate(look);

        //------------------------------
        // Render
        //------------------------------
        Renderer::Draw();
        
        //------------------------------
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        //------------------------------
        glfwSwapBuffers(_window.GetGlWindow());
        glfwPollEvents();
    }

    //------------------------------
    // glfw: terminate, clearing all previously allocated GLFW resources.
    //------------------------------
    glfwTerminate();
}
