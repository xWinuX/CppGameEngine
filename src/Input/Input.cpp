#include "Input.h"

#include <map>
#include <GLFW/glfw3.h>

#include "../Application.h"

using namespace GameEngine::Input;

void Input::Update() { glfwPollEvents(); }

bool Input::GetKeyDown(const int key) { return glfwGetKey(Application::GetWindow().GetGlWindow(), key) == GLFW_PRESS; }

bool Input::GetKeyPressed(const int key)
{
    static std::map<int, bool> keyStates;
    
    if (glfwGetKey(Application::GetWindow().GetGlWindow(), key) == GLFW_PRESS)
    {
        if (!keyStates[key])
        {
            keyStates[key] = true;
            return true;
        }
    }
    else
    {
        keyStates[key] = false;
    }

    return false;
}
