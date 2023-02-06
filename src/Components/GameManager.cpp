#include "GameManager.h"

#include "GameEngine/Cursor.h"
#include "GameEngine/Input.h"
#include "GameEngine/Debug/DebugGUIManager.h"
#include "GameEngine/Physics/PhysicsManager.h"

void GameManager::OnUpdate()
{
    if (GameEngine::Input::GetKeyPressed(GLFW_KEY_ESCAPE)) { DebugGUIManager::ToggleHidden(); }
    
    if (GameEngine::Input::GetKeyPressed(GLFW_KEY_P)) { GameEngine::Physics::PhysicsManager::ToggleDebugWireframe(); }

    if (DebugGUIManager::IsHidden()) { Cursor::Lock(); }
    else { Cursor::Unlock(); }
}
