#include "Window.h"

#include "../Debug/Log.h"

using namespace GameEngine::Core;

Window::Window(const glm::ivec2 initialSize) { _size = initialSize; }

void Window::DestroyGLWindow() const { if (_glWindow != nullptr) { glfwDestroyWindow(_glWindow); } }

Window::~Window() { DestroyGLWindow(); }

void Window::FramebufferSizeCallback(GLFWwindow* glWindow, int width, int height)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
    window->SetSize(glm::ivec2(width, height));
    for (const auto& resizeCallback : window->GetResizeCallbacks()) { resizeCallback(window); }
    const glm::ivec2 size = window->GetSize();
    glViewport(0, 0, size.x, size.y);
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
        Debug::Log::Error("Failed to create GLFW window");
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

void Window::AddFramebufferSizeCallback(const std::function<void(Window*)>& callbackFunction) { _resizeCallbacks.push_back(callbackFunction); }

bool Window::ShouldClose() const { return glfwWindowShouldClose(_glWindow); }

glm::ivec2 Window::GetSize() const { return _size; }

std::vector<std::function<void(Window*)>>& Window::GetResizeCallbacks() { return _resizeCallbacks; }

GLFWwindow* Window::GetGlWindow() const { return _glWindow; }
