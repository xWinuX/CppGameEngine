#include "GameEngine/Cursor.h"

#include "GameEngine/Window.h"
#include "GLFW/glfw3.h"

void Cursor::Lock() { glfwSetInputMode(GameEngine::Window::GetCurrentWindow()->GetGlWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); }

void Cursor::Unlock() { glfwSetInputMode(GameEngine::Window::GetCurrentWindow()->GetGlWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
