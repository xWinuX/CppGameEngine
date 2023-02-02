#include "GameManager.h"

#include "GameEngine/Cursor.h"
#include "GameEngine/Input.h"
#include "GameEngine/Debug/DebugGUIManager.h"

void GameManager::OnUpdate()
{
    if (GameEngine::Input::GetKeyPressed(GLFW_KEY_ESCAPE)) { DebugGUIManager::ToggleHidden(); }

    if (DebugGUIManager::IsHidden()) { Cursor::Lock(); }
    else { Cursor::Unlock(); }
}
