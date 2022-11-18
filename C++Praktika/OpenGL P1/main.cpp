#include <array>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
void framebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
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
    // Initialize Shaders and Materials
    // ------------------------------
    Shader defaultShader = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");
    const GLchar* u_Color = "u_Color";
    defaultShader.InitializeUniform4F(u_Color);

    Material triangleMaterial = Material(&defaultShader);
    triangleMaterial.SetUniform4F(u_Color, {0.0f, 0.0f, 1.0f, 1.0f});

    Material wideTriangleMaterial = Material(&defaultShader);
    wideTriangleMaterial.SetUniform4F(u_Color, {1.0f, 0.0f, 0.0f, 1.0f});

    // ------------------------------
    // Initialize Meshes 
    // ------------------------------
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
        &triangleMaterial
    };

    float wideTrianglePositions[9] = {
        -0.9f, -0.25f, 0.0f,
        0.0f, 0.9f, 0.0f,
        0.9f, -0.25f, 0.0f,
    };
    GLubyte wideTriangleIndices[3] = {0, 1, 2};

    const MeshData wideTriangleMeshData = {
        &wideTrianglePositions[0],
        &wideTriangleIndices[0],
        sizeof(wideTrianglePositions) / sizeof(float),
        sizeof(wideTriangleIndices) / sizeof(GLubyte)
    };

    const Mesh wideTriangleMesh = {
        &wideTriangleMeshData,
        &wideTriangleMaterial
    };

    // ------------------------------
    // Initialize Vertex Array Object
    // ------------------------------
    const VertexAttribute defaultVertexAttributes[1] = {
        VertexAttribute(3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr)
    };

    VertexArrayObject vertexArrayObject = VertexArrayObject(defaultVertexAttributes, sizeof(defaultVertexAttributes) / sizeof(VertexAttribute));

    vertexArrayObject.AddMesh(&triangleMesh);
    vertexArrayObject.AddMesh(&wideTriangleMesh);

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
        // Input
        //------------------------------

        // Close Window if escape key is pressed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }

        // Change Polygon Mode
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) { glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); }
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
        
        //------------------------------
        // Render
        //------------------------------
        glClearColor(0.15f, 0.25f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        triangleMaterial.SetUniform4F(u_Color, {sin01(currentTime), sin01(currentTime + 1), sin01(currentTime + 2), 1.0f});
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
