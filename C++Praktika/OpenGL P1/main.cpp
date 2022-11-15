#include <array>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "src/Rendering/Mesh.h"
#include "src/Rendering/Shader.h"
#include "src/Rendering/VertexArrayObject.h"
#include "src/Rendering/VertexAttribute.h"
#include "src/Rendering/VertexAttributes.h"

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
    // Initialize Mesh
    // ------------------------------

    float positions[9]{
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };
    constexpr unsigned int positionsCount = sizeof(positions) / sizeof(float);

    unsigned int           indices[3]   = {0, 1, 2};
    constexpr unsigned int indicesCount = sizeof(indices) / sizeof(unsigned int);


    std::cout << positionsCount << std::endl;
    std::cout << indicesCount << std::endl;

    const Mesh mesh = Mesh(positions, indices, positionsCount, indicesCount);

    const VertexAttribute defaultVertexAttributes[1] = {
        VertexAttribute(3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr)
    };
    const VertexAttributes defaultAttributes = VertexAttributes(defaultVertexAttributes, sizeof(defaultAttributes));

    VertexArrayObject vertexArrayObject = VertexArrayObject();

    // Build VBO
    vertexArrayObject.Bind();
    defaultAttributes.Bind();

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glBufferData(GL_ARRAY_BUFFER, mesh.GetPositionsCount() * sizeof(float), positions, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndicesCount() * sizeof(GLubyte), indices, GL_STATIC_DRAW);

    vertexArrayObject.Bind();

    // ------------------------------
    // Render Loop
    // ------------------------------
    const Shader defaultShader = Shader("res/shaders/DefaultShader.vsh", "res/shaders/DefaultShader.fsh");

    defaultShader.Use();

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
        glClearColor(sin01(currentTime), 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vertexArrayObject.Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, nullptr);

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
