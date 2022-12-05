#include "Application.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Core/Window.h"
#include "Components/TransformComponent.h"
#include "Rendering/Buffers/IndexBuffer.h"
#include "Rendering/Material.h"
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include "Rendering/Buffers/VertexBufferAttribute.h"
#include "Rendering/Buffers/VertexBuffer.h"

#define INITIAL_WINDOW_WIDTH  800
#define INITIAL_WINDOW_HEIGHT 600

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

Application::Application() { glfwInit(); }

void Application::Run(const glm::ivec2 initialWindowSize)
{
    Window window = Window(initialWindowSize);
    _window       = &window;

    // Resize Projection Matrix with new size
    updateProjectionMatrix(screenWidth, screenHeight, currentFOV);

    // Set Callbacks
    glfwSetKeyCallback(GetWindow().GetGlWindow(), keyCallback);

    // ------------------------------
    // GLAD: load all OpenGL function pointers
    // ------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) { std::cout << "Failed to initialize GLAD" << std::endl; }

    // ------------------------------
    // Initialize Shaders and Materials
    // ------------------------------
    Shader defaultShader = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");

    const GLchar* u_Color          = "u_Color";
    const GLchar* u_Model          = "u_Model";
    const GLchar* u_ViewProjection = "u_ViewProjection";

    defaultShader.InitializeUniform(u_Color);
    defaultShader.InitializeUniform(u_Model);
    defaultShader.InitializeUniform(u_ViewProjection);

    Material defaultMaterial = Material(&defaultShader);

    defaultMaterial.SetUniform4F(u_Color, {0.0f, 0.0f, 1.0f, 1.0f});

    // ------------------------------
    // Initialize Mesh Data
    // ------------------------------
    #pragma region Cube

    VertexPos cubeVertices[8] = {
        // Front
        {{-1.0f, -1.0f, 1.0f}}, // 0 Front Top Left
        {{1.0f, -1.0f, 1.0f}},  // 1 Front Top Right
        {{-1.0f, 1.0f, 1.0f}},  // 2 Front Bottom Left
        {{1.0f, 1.0f, 1.0f}},   // 3 Front Bottom Right

        // Back
        {{-1.0f, -1.0f, -1.0f}}, // 0 Back Top Left
        {{1.0f, -1.0f, -1.0f}},  // 1 Back Top Right
        {{-1.0f, 1.0f, -1.0f}},  // 2 Back Bottom Left
        {{1.0f, 1.0f, -1.0f}},   // 3 Back Bottom Right
    };
    VertexBuffer cubeVertexBuffer = VertexBuffer(cubeVertices, sizeof(cubeVertices) / sizeof(VertexPos));

    GLubyte cubeIndices[36] = {
        // Front Face
        0, 1, 2, // First Triangle
        1, 3, 2, // Second Triangle

        // Right Face
        1, 5, 3, // First Triangle
        5, 7, 3, // Second Triangle

        // Left Face
        0, 6, 4, // First Triangle
        6, 0, 2, // Second Triangle

        // Top Face
        1, 0, 4, // First Triangle
        1, 4, 5, // Second Triangle

        // Bottom Face
        2, 3, 7, // First Triangle
        6, 2, 7, // Second Triangle

        // Back Face
        7, 5, 4, // First Triangle
        4, 6, 7  // Second Triangle
    };
    IndexBuffer cubeIndexBuffer = IndexBuffer(cubeIndices, sizeof(cubeIndices) / sizeof(GLubyte));

    const Mesh cubeMeshData = {
        &cubeVertexBuffer,
        &cubeIndexBuffer
    };

    #pragma endregion

    // ------------------------------
    // Initialize Vertex Array Object
    // ------------------------------
    const VertexBufferAttribute defaultVertexAttributes[1] = {
        VertexBufferAttribute(3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr),
    };

    //VertexArrayObject vertexArrayObject = VertexArrayObject(defaultVertexAttributes, sizeof(defaultVertexAttributes) / sizeof(VertexBufferAttribute));

    // ------------------------------
    // Create Renderable Meshes
    // ------------------------------

    // vertexArrayObject.AddMesh(&cubeMesh);
    //vertexArrayObject.PrepareMeshes();

    // ------------------------------
    // Render Loop
    // ------------------------------
    TransformComponent modelTransform;
    TransformComponent cameraTransform;
    modelTransform.SetPosition(glm::vec3(0.0f, 0.0f, -6.0f));

    float currentTime = getCurrentTime();
    while (!glfwWindowShouldClose(GetWindow().GetGlWindow()))
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

        //------------------------------
        // Render
        //------------------------------
        glClearColor(0.15f, 0.25f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //vertexArrayObject.Draw();

        //------------------------------
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        //------------------------------
        glfwSwapBuffers(GetWindow().GetGlWindow());
        glfwPollEvents();
    }

    //------------------------------
    // glfw: terminate, clearing all previously allocated GLFW resources.
    //------------------------------
    glfwTerminate();
}
