#include <array>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "src/Math/Vector4.h"
#include "src/Rendering/Material.h"
#include "src/Rendering/Mesh.h"
#include "src/Rendering/MeshData.h"
#include "src/Rendering/Shader.h"
#include "src/Rendering/VertexArrayObject.h"
#include "src/Rendering/VertexAttribute.h"

#define INITIAL_WINDOW_WIDTH  800
#define INITIAL_WINDOW_HEIGHT 600

//------------------------------
// glfw: whenever the window size changed (by OS or user resize input) this callback function executes
//------------------------------

glm::mat4 projectionMatrix = glm::mat4(1.0f);

void resizeProjectionMatrix(const float screenWidth, const float screenHeight) { projectionMatrix = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1000.0f, 1000.0f); }

void framebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
    const float screenWidth  = static_cast<float>(width);
    const float screenHeight = static_cast<float>(height);
    resizeProjectionMatrix(screenWidth, screenHeight);
}

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
        if (cull)
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CW);
        }
        else { glDisable(GL_CULL_FACE); }
    }
}

float getCurrentTime() { return static_cast<float>(glfwGetTime()); }

float sin01(const float x) { return (sin(x) + 1.0f) / 2.0f; }

int main()
{
    //-------------------------------
    // Initialize and configure
    // ------------------------------
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ------------------------------
    // GLFW Window creation
    // ------------------------------
    GLFWwindow* window = glfwCreateWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "SAE OpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Resize Projection Matrix with new size
    resizeProjectionMatrix(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT);

    // Set Callbacks
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    // ------------------------------
    // GLAD: load all OpenGL function pointers
    // ------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ------------------------------
    // Initialize Shaders and Materials
    // ------------------------------
    Shader defaultShader = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");

    const GLchar* u_Color      = "u_Color";
    const GLchar* u_Model      = "u_Model";
    const GLchar* u_View       = "u_View";
    const GLchar* u_Projection = "u_Projection";

    defaultShader.InitializeUniform(u_Color);
    defaultShader.InitializeUniform(u_Model);
    defaultShader.InitializeUniform(u_View);
    defaultShader.InitializeUniform(u_Projection);

    Material defaultMaterial = Material(&defaultShader);

    defaultMaterial.SetUniform4F(u_Color, {0.0f, 0.0f, 1.0f, 1.0f});

    // ------------------------------
    // Initialize Mesh Data
    // ------------------------------
    #pragma region Quad
    constexpr float centerX           = INITIAL_WINDOW_WIDTH / 2.0f;
    constexpr float centerY           = INITIAL_WINDOW_HEIGHT / 2.0f;
    float           quadPositions[12] = {
        centerX - 200.0f, centerY - 200.0f, 0.0f, // 0 Top Left
        centerX + 200.0f, centerY - 200.0f, 0.0f, // 1 Top Right
        centerX - 200.0f, centerY + 200.0f, 0.0f, // 2 Bottom Left
        centerX + 200.0f, centerY + 200.0f, 0.0f  // 3 Bottom Right
    };
    GLubyte quadIndices[6] = {
        0, 1, 2, // First Triangle
        3, 2, 1  // Second Triangle
    };

    const MeshData quadMeshData = {
        &quadPositions[0],
        &quadIndices[0],
        sizeof(quadPositions) / sizeof(float),
        sizeof(quadIndices) / sizeof(GLubyte)
    };
    #pragma endregion

    #pragma region Cube
    float cubePositions[24] = {
        // Front
        centerX - 200.0f, centerY - 200.0f, 0.0f, // 0 Front Top Left
        centerX + 200.0f, centerY - 200.0f, 0.0f, // 1 Front Top Right
        centerX - 200.0f, centerY + 200.0f, 0.0f, // 2 Front Bottom Left
        centerX + 200.0f, centerY + 200.0f, 0.0f,  // 3 Front Bottom Right

        // Back
        centerX - 200.0f, centerY - 200.0f, 200.0f, // 0 Back Top Left
        centerX + 200.0f, centerY - 200.0f, 200.0f, // 1 Back Top Right
        centerX - 200.0f, centerY + 200.0f, 200.0f, // 2 Back Bottom Left
        centerX + 200.0f, centerY + 200.0f, 200.0f,  // 3 Back Bottom Right
    };
    GLubyte cubeIndices[36] = {
        // Front Face
        0, 1, 2, // First Triangle
        1, 3, 2, // Second Triangle

        // Right Face
        1, 5, 3, // First Triangle
        5, 7, 3, // Second Triangle

        // Left Face
        0, 2, 4, // First Triangle
        4, 2, 6, // Second Triangle

        // Top Face
        1, 0, 4, // First Triangle
        1, 4, 5, // Second Triangle

        // Bottom Face
        2, 3, 6, // First Triangle
        3, 7, 6, // Second Triangle

        // Back Face
        6, 5, 4, // First Triangle
        6, 7, 5  // Second Triangle
    };

    const MeshData cubeMeshData = {
        &cubePositions[0],
        &cubeIndices[0],
        sizeof(cubePositions) / sizeof(float),
        sizeof(cubeIndices) / sizeof(GLubyte)
    };
    #pragma endregion

    // ------------------------------
    // Initialize Vertex Array Object
    // ------------------------------
    const VertexAttribute defaultVertexAttributes[1] = {
        VertexAttribute(3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr)
    };

    VertexArrayObject vertexArrayObject = VertexArrayObject(defaultVertexAttributes, sizeof(defaultVertexAttributes) / sizeof(VertexAttribute));

    // ------------------------------
    // Create Renderable Meshes
    // ------------------------------
    const Mesh quadMesh = {&quadMeshData, &defaultMaterial};
    const Mesh cubeMesh = {&cubeMeshData, &defaultMaterial};

    vertexArrayObject.AddMesh(&cubeMesh);
    vertexArrayObject.PrepareMeshes();

    // ------------------------------
    // Render Loop
    // ------------------------------
    float currentTime = getCurrentTime();
    while (!glfwWindowShouldClose(window))
    {
        //------------------------------
        // Time
        //------------------------------
        const float newTime   = getCurrentTime();
        float       deltaTime = newTime - currentTime;
        currentTime           = newTime;

        //------------------------------
        // Render
        //------------------------------
        glClearColor(0.15f, 0.25f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f); // Set to identity matrix first
        glm::mat4 view  = glm::mat4(1.0f);

        model = translate(model, glm::vec3(0.0f, 0.0f, 3.0f));
        view  = translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

        defaultMaterial.SetUniformMat4F(u_Model, model);
        defaultMaterial.SetUniformMat4F(u_View, view);
        defaultMaterial.SetUniformMat4F(u_Projection, projectionMatrix);

        defaultMaterial.SetUniform4F(u_Color, {sin01(currentTime), sin01(currentTime + 1), sin01(currentTime + 2), 1.0f});
        vertexArrayObject.Draw();

        //------------------------------
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        //------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //------------------------------
    // glfw: terminate, clearing all previously allocated GLFW resources.
    //------------------------------
    glfwTerminate();
    return 0;
}
