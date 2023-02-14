#include "GameManager.h"

#include "GameEngine/Cursor.h"
#include "GameEngine/Input.h"
#include "GameEngine/GUIManager.h"
#include "GameEngine/Physics/PhysicsManager.h"
#include "../Asset.h"
#include "../Prefabs/CratePrefab.h"
#include "GameEngine/Components/MeshRenderer.h"

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

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    if (ImGui::Button(GetImGuiIDString("Create Cube").c_str())) { _cratePrefab.Instantiate(glm::uvec3(0.0f, 10.0f, 0.0f)); }
    ImGui::SameLine();

    if (ImGui::Button(GetImGuiIDString("Create Gamer Dude").c_str()))
    {
        const GameObject* gameObject = _cubeManPrefab.Instantiate(glm::uvec3(0.0f, 10.0f, 0.0f));
        gameObject->GetTransform()->SetLocalScale(glm::linearRand(0.2f, 4.0f) * glm::vec3(1.0));
    }
    ImGui::SameLine();

    if (ImGui::Button(GetImGuiIDString("Create Porcelain Sphere").c_str()))
    {
        GameObject* gameObject = _rigidbodySpherePrefab.Instantiate();
        gameObject->GetComponent<Components::MeshRenderer>()->SetMaterial(GET_MATERIAL(Porcelain));
    }
    ImGui::SameLine();


    if (ImGui::Button(GetImGuiIDString("Create Mirror Sphere").c_str()))
    {
        GameObject* gameObject = _rigidbodySpherePrefab.Instantiate();
        gameObject->GetComponent<Components::MeshRenderer>()->SetMaterial(GET_MATERIAL(Mirror));
    }

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    if (ImGui::CollapsingHeader("Material Properties"))
    {
        ImGui::Indent();
        const std::map<Asset::Material, Material*> materials = AssetDatabase::GetAll<Asset::Material, Material*>();
        for (const std::pair<const Asset::Material, Material*> material : materials) { material.second->DrawProperties(); }
        ImGui::Unindent();
    }

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
}
