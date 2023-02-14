#include "GameManager.h"

#include "GameEngine/Cursor.h"
#include "GameEngine/Input.h"
#include "GameEngine/GUIManager.h"
#include "GameEngine/Physics/PhysicsManager.h"
#include "../Asset.h"
#include "../Prefabs/CratePrefab.h"

using namespace GameEngine;
using namespace GameEngine::Rendering;

std::map<std::string, Texture2D*> textureMap   = std::map<std::string, Texture2D*>();
std::vector<std::string>          textureNames = std::vector<std::string>(10);

const char* currentSelectedTexture;

GameManager::GameManager():
    Component("Game Manager") {}

void GameManager::OnUpdate()
{
    if (GameEngine::Input::GetKeyPressed(GLFW_KEY_ESCAPE)) { GUIManager::ToggleHidden(); }

    if (GameEngine::Input::GetKeyPressed(GLFW_KEY_P)) { Physics::PhysicsManager::ToggleDebugWireframe(); }
    if (GameEngine::Input::GetKeyPressed(GLFW_KEY_F))
    {
        _fullscreen = !_fullscreen;
        Window::GetCurrentWindow()->SetFullscreen(_fullscreen);
    }

    if (GUIManager::IsHidden()) { Cursor::Lock(); }
    else { Cursor::Unlock(); }

    if (ImGui::Button(GetImGuiIDString("Close Application").c_str())) { Window::GetCurrentWindow()->Close(); }

    if (ImGui::Button(GetImGuiIDString("Create Cube").c_str())) { _cratePrefab.Instantiate(glm::uvec3(0.0f, 10.0f, 0.0f)); }
    
    if (ImGui::Button(GetImGuiIDString("Create Cube Man").c_str()))
    {
        const GameObject* gameObject = _cubeManPrefab.Instantiate(glm::uvec3(0.0f, 10.0f, 0.0f));
        gameObject->GetTransform()->SetLocalScale(glm::linearRand(0.05f, 4.0f) * glm::vec3(1.0));
    }

    if (ImGui::CollapsingHeader("Material Properties"))
    {
        ImGui::Indent();
        const std::map<Asset::Material, Material*> materials = AssetDatabase::GetAll<Asset::Material, Material*>();
        for (const std::pair<const Asset::Material, Material*> material : materials) { material.second->DrawProperties(); }
        ImGui::Unindent();
    }
}
