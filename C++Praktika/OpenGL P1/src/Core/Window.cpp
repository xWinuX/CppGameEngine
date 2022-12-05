#include "Window.h"
#include <iostream>

Window::Window(const glm::ivec2 initialSize) { _size = initialSize; }

void Window::DestroyGLWindow() const { if (_glWindow != nullptr) { glfwDestroyWindow(_glWindow); } }

Window::~Window() { DestroyGLWindow(); }

void Window::FramebufferSizeCallback(GLFWwindow* glWindow, int width, int height)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
    for (const auto resizeCallback : window->GetResizeCallbacks()) { resizeCallback(nullptr); }
}

void Window::CreateContext()
{
    // Destroy current gl window if one already exists
    if (_glWindow != nullptr) { DestroyGLWindow(); }

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

void Window::SetSize(const glm::ivec2 newSize)
{
    _size = newSize;
    glfwSetWindowSize(_glWindow, newSize.x, newSize.y);
}

glm::ivec2 Window::GetSize() const { return _size; }

std::vector<Window::WindowResizeCallbackFunction>& Window::GetResizeCallbacks() { return _resizeCallbacks; }

GLFWwindow* Window::GetGlWindow() const { return _glWindow; }
