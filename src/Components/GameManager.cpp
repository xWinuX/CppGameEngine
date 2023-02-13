#include "GameManager.h"

#include "GameEngine/Cursor.h"
#include "GameEngine/Input.h"
#include "GameEngine/Debug/DebugGUIManager.h"
#include "GameEngine/Physics/PhysicsManager.h"
#include "../Asset.h"

using namespace GameEngine;
using namespace GameEngine::Rendering;

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
    
    // Draw Material UI
    if (ImGui::CollapsingHeader("Material Properties"))
    {
        ImGui::Indent();
        const std::map<Asset::Material, Material*> materials = AssetDatabase::GetAll<Asset::Material, Material*>();
        for (const std::pair<const Asset::Material, Material*> material : materials) { material.second->DrawProperties(); }
        ImGui::Unindent();
    }
}
