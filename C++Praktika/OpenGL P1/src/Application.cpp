#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Components/MeshRendererComponent.h"
#include "Core/Window.h"
#include "Components/TransformComponent.h"
#include "Core/Scene.h"
#include "Rendering/Material.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/Buffers/VertexBufferAttribute.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Shapes/Cube.h"

#define INITIAL_WINDOW_WIDTH  800
#define INITIAL_WINDOW_HEIGHT 600

Window Application::_window = Window(glm::ivec2(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT));

glm::mat4 projectionMatrix = glm::mat4(1.0f);

float currentFOV        = 60;
float currentViewWidth  = INITIAL_WINDOW_WIDTH;
float currentViewHeight = INITIAL_WINDOW_WIDTH;

float screenWidth  = INITIAL_WINDOW_WIDTH;
float screenHeight = INITIAL_WINDOW_HEIGHT;

bool cull = false;

void updateProjectionMatrix(const float width, const float height, const float fov)
{
    const float aspectRatio = screenWidth / screenHeight;
    currentViewWidth        = width;
    currentViewHeight       = height;
    currentFOV              = fov;
    projectionMatrix        = glm::perspective(glm::radians(currentFOV), aspectRatio, 0.1f, 100.0f);
}

void framebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
    screenWidth  = static_cast<float>(width);
    screenHeight = static_cast<float>(height);
    updateProjectionMatrix(screenWidth, screenHeight, currentFOV);
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

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) { std::cout << "Failed to initialize GLAD" << std::endl; }
}



void Application::Run() const
{
    std::cout << "Run enter" << std::endl;
    Scene scene = Scene();
    
    Shader defaultShader = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");

    const GLchar* u_Color          = "u_Color";
    const GLchar* u_Model          = "u_Model";

    std::cout << "before uniforms" << std::endl;
    
    defaultShader.InitializeUniform(u_Color);
    defaultShader.InitializeUniform(u_Model);

    std::cout << "after uniforms" << std::endl;

    Material defaultMaterial = Material(&defaultShader);


    std::cout << "before game object" << std::endl;

    GameObject cameraObject = GameObject();
    GameObject cubeObject = GameObject();


    
    Cube cube = Cube();

    std::cout << "Before meshrenderer" << std::endl;
    MeshRendererComponent meshRenderer = MeshRendererComponent(cube.GetMesh(), &defaultMaterial); 
    cubeObject.AddComponent(meshRenderer);
    std::cout << "after meshrenderer" << std::endl;

    
    scene.AddGameObject(cubeObject);

    std::cout << "Before proj" << std::endl;
    
    // Resize Projection Matrix with new size
    updateProjectionMatrix(screenWidth, screenHeight, currentFOV);

    // Set Callbacks
    glfwSetKeyCallback(_window.GetGlWindow(), keyCallback);

    // ------------------------------
    // Initialize Shaders and Materials
    // ------------------------------
    defaultMaterial.SetUniform4F(u_Color, {0.0f, 0.0f, 1.0f, 1.0f});
    
    // ------------------------------
    // Render Loop
    // ------------------------------


    std::cout << "Before main loop" << std::endl;
    
    float currentTime = getCurrentTime();
    while (!glfwWindowShouldClose(_window.GetGlWindow()))
    {
        //------------------------------
        // Time
        //------------------------------
        const float newTime   = getCurrentTime();
        float       deltaTime = newTime - currentTime;
        currentTime           = newTime;

        std::cout << "deltaTime: " << deltaTime << std::endl;

        //------------------------------
        // Gameplay
        //------------------------------
        scene.RunScene();
        /*
        updateProjectionMatrix(currentViewWidth, currentViewHeight, lerp(45.0f, 90.0f, sin01(currentTime)));

        glm::vec3 velocity = glm::vec3(0.0f);
        //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { velocity.x += 5.0f * deltaTime; }
        //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { velocity.x -= 5.0f * deltaTime; }
        //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { velocity.y += 5.0f * deltaTime; }
        //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { velocity.y -= 5.0f * deltaTime; }

        modelTransform.Move(velocity);

        modelTransform.Rotate(glm::vec3(45.0f, 45.0f, 45.0f) * deltaTime);

        defaultMaterial.SetUniformMat4F(u_Model, modelTransform.GetTRS());
        defaultMaterial.SetUniformMat4F(u_ViewProjection, cameraTransform.GetTRS() * projectionMatrix);

        defaultMaterial.SetUniform4F(u_Color, {sin01(currentTime), sin01(currentTime + 1), sin01(currentTime + 2), 1.0f});
        */
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
