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

#include "GameEngine/Debug/DebugGUIManager.h"
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
    PhysicsManager::Initialize();
    AudioManager::Initialize();
    DebugGUIManager::Initialize();
}

void Application::Run()
{
    Scene scene = Scene();

    Initialize(scene);

    scene.InitializeScene();

    while (!_window.ShouldClose())
    {
        DebugGUIManager::BeginNewFrame();
        
        Time::Update();
        Input::Update();
        
        // Executes als OnPhysicsUpdates on game objects if a physics time step happens, also updates the physics world
        PhysicsManager::Update(&scene);
        
        // Execute Update calls on each game object in the current scene
        scene.OnUpdate();
        
        // Audio Update
        AudioManager::Update();
        
        // Render
        Renderer::RenderSubmitted();
        
        // Render dear imgui into screen
        DebugGUIManager::Draw();
        
        Renderer::DrawFrame();
        
        std::cout << "FPS: " << std::to_string(1 / Time::GetDeltaTime()) << std::endl;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    OnEnd();

    glfwTerminate();
}
