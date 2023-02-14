#include "GameEngine/Gui.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GameEngine/Window.h"

using namespace GameEngine;

bool Gui::_isHidden = false;

void Gui::Initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(GameEngine::Window::GetCurrentWindow()->GetGlWindow(), true);
    ImGui_ImplOpenGL3_Init();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui::SetNextWindowSize({500, 500});
}

void Gui::BeginNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Application Control");
}

void Gui::Draw()
{
    ImGui::End();
    ImGui::Render();

    if (!_isHidden) { ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); }
}

bool Gui::IsHidden() { return _isHidden; }
void Gui::SetHidden(const bool hidden) { _isHidden = hidden; }
void Gui::ToggleHidden() { _isHidden = !_isHidden; }
