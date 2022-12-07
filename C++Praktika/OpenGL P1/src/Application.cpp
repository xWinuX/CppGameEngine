#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include <glm/ext/matrix_transform.hpp>

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

#define INITIAL_WINDOW_WIDTH  800
#define INITIAL_WINDOW_HEIGHT 600

Window Application::_window = Window(glm::ivec2(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT));



bool cull = false;


void framebufferSizeCallback(Window* window)
{
    const glm::vec2 size = window->GetSize();
    glViewport(0, 0, size.x, size.y);

}

float lerp(const float a, const float b, const float t) { return a + (b - a) * t; }

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

float sin01(const float x) { return (sin(x) + 1.0f) / 2.0f; }

Application::Application()
{
    glfwInit();

    _window.CreateContext();
    _window.AddFramebufferSizeCallback(framebufferSizeCallback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) { std::cout << "Failed to initialize GLAD" << std::endl; }
}



void Application::Run() const
{
    Scene scene = Scene();
    
    Shader defaultShader = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");
    
    Material defaultMaterial = Material(&defaultShader);
    
    GameObject cameraObject = GameObject();
    CameraComponent cameraComponent = CameraComponent(60, 0.01f, 1000.0f);
    cameraObject.AddComponent(&cameraComponent);

    GameObject cubeObject = GameObject();
    Cube cube = Cube();
    MeshRendererComponent meshRenderer = MeshRendererComponent(cube.GetMesh(), &defaultMaterial); 
    cubeObject.AddComponent(&meshRenderer);

    cubeObject.GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, 20.0f));
    
    scene.AddGameObject(cubeObject);
    scene.AddGameObject(cameraObject);

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

       // std::cout << "deltaTime: " << deltaTime << std::endl;

        //------------------------------
        // Gameplay
        //------------------------------
        scene.UpdateScene();


        glm::vec3 velocity = glm::vec3(0.0f);
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_D) == GLFW_PRESS) { velocity.x += 5.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_A) == GLFW_PRESS) { velocity.x -= 5.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_W) == GLFW_PRESS) { velocity.y += 5.0f * deltaTime; }
        if (glfwGetKey(_window.GetGlWindow(), GLFW_KEY_S) == GLFW_PRESS) { velocity.y -= 5.0f * deltaTime; }

        cameraObject.GetTransform().Move(velocity);
        
        //------------------------------
        // Render
        //------------------------------
        glClearColor(0.15f, 0.25f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        Renderer::Draw();

        //vertexArrayObject.Draw();

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
