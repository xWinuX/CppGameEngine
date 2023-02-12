#include "GameManager.h"

#include "GameEngine/Cursor.h"
#include "GameEngine/Input.h"
#include "GameEngine/Debug/DebugGUIManager.h"
#include "GameEngine/Physics/PhysicsManager.h"

using namespace GameEngine;

void GameManager::OnUpdate()
{
    if (GameEngine::Input::GetKeyPressed(GLFW_KEY_ESCAPE)) { DebugGUIManager::ToggleHidden(); }
    
    if (GameEngine::Input::GetKeyPressed(GLFW_KEY_P)) { Physics::PhysicsManager::ToggleDebugWireframe(); }
    if (GameEngine::Input::GetKeyPressed(GLFW_KEY_F))
    {
        _fullscreen = !_fullscreen;
        Window::GetCurrentWindow()->SetFullscreen(_fullscreen);
    }

    if (DebugGUIManager::IsHidden()) { Cursor::Lock(); }
    else { Cursor::Unlock(); }
}
