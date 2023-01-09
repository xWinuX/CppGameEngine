#include "Input.h"

#include <map>

using namespace GameEngine::Input;

void Input::Update() { glfwPollEvents(); }

bool Input::GetKeyDown(const int key) { return glfwGetKey(Core::Window::GetCurrentWindow()->GetGlWindow(), key) == GLFW_PRESS; }

bool Input::GetKeyPressed(const int key)
{
    static std::map<int, bool> keyStates;

    if (glfwGetKey(Core::Window::GetCurrentWindow()->GetGlWindow(), key) == GLFW_PRESS)
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
