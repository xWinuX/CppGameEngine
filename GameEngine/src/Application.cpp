#include "GameEngine/Application.h"

#include <imgui.h>
#include <tiny_gltf.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GameEngine/Input.h"
#include "GameEngine/Time.h"
#include "GameEngine/Audio/AudioManager.h"
#include "GameEngine/IO/Importer/GLTF.h"
#include "GameEngine/IO/Importer/GLTF.h"
#include "GameEngine/IO/Importer/GLTF.h"
#include "GameEngine/Physics/PhysicsManager.h"
#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine;
using namespace GameEngine::Debug;
using namespace GameEngine::Rendering;
using namespace GameEngine::Physics;
using namespace GameEngine::Audio;

Application::Application()
{
    glfwInit();
    
    _window.CreateContext();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) { Log::Error("Failed to initialize GLAD"); }
    
    // Initialize Systems
    Renderer::Initialize();
    Audio::AudioManager::Initialize();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(Window::GetCurrentWindow()->GetGlWindow(), true);
    ImGui_ImplOpenGL3_Init();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui::SetNextWindowSize({200, 200});

}

void Application::Run()
{
    Scene scene = Scene();

    Initialize(scene);

    scene.InitializeScene();

    while (!_window.ShouldClose())
    {
        
        Time::Update();
        Input::Update();

        // Executes als OnPhysicsUpdates on game objects if a physics time step happens, also updates the physics world
        PhysicsManager::Update(&scene);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Demo window");
        
        // Execute Update calls on each game object in the current scene
        scene.Update();
        
        CustomRun();

        // Audio Update
        AudioManager::Update();
        
        // Render
        Renderer::RenderSubmitted();


        
        GuiDraw();
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        Renderer::DrawFrame();

        std::cout << "FPS: " << std::to_string(1 / Time::GetDeltaTime()) << std::endl;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    OnEnd();

    glfwTerminate();
}
