#include "GameEngine/Input.h"

#include <map>

using namespace GameEngine;

glm::vec2 Input::_previousMousePosition = glm::zero<glm::vec2>();

void Input::Update()
{
    _previousMousePosition = GetMousePosition();
    glfwPollEvents();
}

bool Input::GetKeyDown(const int key) { return glfwGetKey(Window::GetCurrentWindow()->GetGlWindow(), key) == GLFW_PRESS; }

bool Input::GetKeyPressed(const int key)
{
    static std::map<int, bool> keyStates;

    if (glfwGetKey(Window::GetCurrentWindow()->GetGlWindow(), key) == GLFW_PRESS)
    {
        if (!keyStates[key])
        {
            keyStates[key] = true;
            return true;
        }
    }
    else { keyStates[key] = false; }

    return false;
}

glm::vec2 Input::GetMousePosition()
{
    double xPos, yPos;
    glfwGetCursorPos(Window::GetCurrentWindow()->GetGlWindow(), &xPos, &yPos);

    return {static_cast<float>(xPos), static_cast<float>(yPos)};
}

glm::vec2 Input::GetMouseDelta() { return _previousMousePosition - GetMousePosition(); }
