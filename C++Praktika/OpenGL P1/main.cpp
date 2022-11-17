#include <array>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
void framebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

//------------------------------
// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//------------------------------
void processInput(GLFWwindow* window)
{
    // Close Window if escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
}

float getCurrentTime() { return static_cast<float>(glfwGetTime()); }

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

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // ------------------------------
    // GLAD: load all OpenGL function pointers
    // ------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ------------------------------
    // Initialize Mesh
    // ------------------------------

    const Shader   defaultShader   = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");
    const Material defaultMaterial = Material(&defaultShader);
    
    float trianglePositions[9] = {
        -0.5f, -0.5f, 1.0f,
        0.0f, 0.5f, 1.0f,
        0.5f, -0.5f, 1.0f,
    };
    GLubyte triangleIndices[3] = {0, 1, 2};

    const MeshData triangleMeshData = {
        &trianglePositions[0],
        &triangleIndices[0],
        sizeof(trianglePositions) / sizeof(float),
        sizeof(triangleIndices) / sizeof(GLubyte)
    };
    
    const Mesh triangleMesh = {
        &triangleMeshData,
        &defaultMaterial
    };
    
    float smallTrianglePositions[9] = {
        -0.25f, -0.25f, 0.0f,
        0.0f, 0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,
    };
    GLubyte smallTriangleIndices[3] = {0, 1, 2};

    const MeshData smallTriangleMeshData = {
        &smallTrianglePositions[0],
        &smallTriangleIndices[0],
        sizeof(smallTrianglePositions) / sizeof(float),
        sizeof(smallTriangleIndices) / sizeof(GLubyte)
    };
    
    const Mesh smallTriangleMesh = {
        &smallTriangleMeshData,
        &defaultMaterial
    };
    
    const VertexAttribute defaultVertexAttributes[1] = {
        VertexAttribute(3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr)
    };

    VertexArrayObject vertexArrayObject = VertexArrayObject(defaultVertexAttributes, sizeof(defaultVertexAttributes) / sizeof(VertexAttribute));

    vertexArrayObject.AddMesh(&triangleMesh);
    vertexArrayObject.AddMesh(&smallTriangleMesh);
    
    vertexArrayObject.Initialize();

    // ------------------------------
    // Render Loop
    // ------------------------------

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    defaultMaterial.UseShader();

    
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
        // Input
        //------------------------------
        processInput(window);

        //------------------------------
        // Render
        //------------------------------
        glClearColor(0.15f, 0.25f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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
