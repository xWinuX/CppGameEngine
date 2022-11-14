#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Rendering/Material.h"
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"

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
    float positions[] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f,
    };

    unsigned int indices[] = {0, 1, 2};

    Mesh mesh = Mesh(positions, indices);

    
    
    // ------------------------------
    // Render Loop
    // ------------------------------
    const Shader   defaultShader   = Shader("test", "test");
    const Material defaultMaterial = Material(&defaultShader);
    
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
