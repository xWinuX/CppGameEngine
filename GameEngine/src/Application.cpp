#include "GameEngine/Application.h"

#include <tiny_gltf.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
        
        // Execute Update calls on each game object in the current scene
        scene.Update();
        
        CustomRun();

        // Audio Update
        AudioManager::Update();

        // Render
        Renderer::Draw();

        std::cout << "FPS: " << std::to_string(1 / Time::GetDeltaTime()) << std::endl;
    }

    OnEnd();

    glfwTerminate();
}
