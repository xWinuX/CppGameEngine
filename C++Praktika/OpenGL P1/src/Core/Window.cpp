#include "Window.h"
#include <iostream>


Window::Window(const glm::ivec2 size)
{
    _size = size;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _glWindow = glfwCreateWindow(_size.x, _size.y, "SAE OpenGL", nullptr, nullptr);
    if (_glWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(_glWindow);
    glfwSetWindowUserPointer(_glWindow, this);
    glfwSetFramebufferSizeCallback(_glWindow, [](GLFWwindow* glWindow, const int x, const int y) { Window::FramebufferSizeCallback(glWindow, x, y); });
}

Window::Window() : Window(glm::ivec2(500, 500)) { }

Window::~Window() { glfwDestroyWindow(_glWindow); }

void Window::FramebufferSizeCallback(GLFWwindow* glWindow, int width, int height)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
    for (const auto resizeCallback : window->GetResizeCallbacks())
    {
        resizeCallback(nullptr);
    }
}
