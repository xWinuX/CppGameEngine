#include "GameEngine/GUIManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GameEngine/Window.h"

using namespace GameEngine;

bool GUIManager::_isHidden = false;

void GUIManager::Initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(GameEngine::Window::GetCurrentWindow()->GetGlWindow(), true);
    ImGui_ImplOpenGL3_Init();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui::SetNextWindowSize({200, 200});
}

void GUIManager::BeginNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Debug Window");
}

void GUIManager::Draw()
{
    ImGui::End();
    ImGui::Render();

    if (!_isHidden) { ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); }
}

bool GUIManager::IsHidden() { return _isHidden; }
void GUIManager::SetHidden(const bool hidden) { _isHidden = hidden; }
void GUIManager::ToggleHidden() { _isHidden = !_isHidden; }
