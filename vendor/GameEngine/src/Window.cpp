#include "GameEngine/Window.h"

#include "GameEngine/Debug/Log.h"

using namespace GameEngine;

Window* Window::_currentWindow = nullptr;

Window::Window(const glm::ivec2 initialSize)
{
    if (_currentWindow != nullptr) { _currentWindow->DestroyGLWindow(); }

    _size          = initialSize;
    _currentWindow = this;
}

Window* Window::GetCurrentWindow() { return _currentWindow; }

void Window::DestroyGLWindow() const { if (_glWindow != nullptr) { glfwDestroyWindow(_glWindow); } }

Window::~Window() { DestroyGLWindow(); }

void Window::FramebufferSizeCallback(GLFWwindow* glWindow, const int width, const int height)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
    window->SetSize(glm::ivec2(width, height));
    for (const auto& resizeCallback : window->GetResizeCallbacks()) { resizeCallback(window); }
    const glm::ivec2 size = window->GetSize();
    glViewport(0, 0, size.x, size.y);
}

void Window::CreateContext()
{
    if (_glWindow != nullptr) { DestroyGLWindow(); }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);

    _glWindow = glfwCreateWindow(static_cast<int>(_size.x), static_cast<int>(_size.y), "CppGameEngine", nullptr, nullptr);
    if (_glWindow == nullptr)
    {
        Debug::Log::Error("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(_glWindow);
    glfwSetWindowUserPointer(_glWindow, this);
    glfwSetFramebufferSizeCallback(_glWindow, [](GLFWwindow* glWindow, const int x, const int y) { Window::FramebufferSizeCallback(glWindow, x, y); });
}

void Window::SetFullscreen(const bool fullscreen)
{
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (fullscreen)
    {
        int xPos, yPos;
        glfwGetWindowPos(_glWindow, &xPos, &yPos);
        _sizeBeforeFullscreen     = _size;
        _positionBeforeFullscreen = glm::uvec2(xPos, yPos);
        glfwSetWindowMonitor(_glWindow, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(
                             _glWindow,
                             nullptr,
                             static_cast<int>(_positionBeforeFullscreen.x),
                             static_cast<int>(_positionBeforeFullscreen.y),
                             static_cast<int>(_sizeBeforeFullscreen.x),
                             static_cast<int>(_sizeBeforeFullscreen.y),
                             mode->refreshRate);
    }
}

void Window::SetSize(const glm::ivec2 newSize)
{
    _size = newSize;
    glfwSetWindowSize(_glWindow, newSize.x, newSize.y);
}

void Window::AddFramebufferSizeCallback(const std::function<void(Window*)>& callbackFunction) { _resizeCallbacks.push_back(callbackFunction); }
void Window::Close() const { glfwSetWindowShouldClose(_glWindow, true); }

bool Window::ShouldClose() const { return glfwWindowShouldClose(_glWindow); }

glm::uvec2 Window::GetSize() const { return _size; }

std::vector<std::function<void(Window*)>>& Window::GetResizeCallbacks() { return _resizeCallbacks; }

GLFWwindow* Window::GetGlWindow() const { return _glWindow; }
