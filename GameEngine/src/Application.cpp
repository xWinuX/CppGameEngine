#include "GameEngine/Application.h"

#include <tiny_gltf.h>

#include "GameEngine/Input.h"
#include "GameEngine/Audio/AudioManager.h"
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

    Renderer::Initialize();
    Audio::AudioManager::Initialize();

    glfwSwapInterval(0);
}

void Application::Run()
{
    Scene scene = Scene();

    Initialize(scene);

    scene.InitializeScene();

    while (!_window.ShouldClose())
    {
        // Update delta time
        Time::Update();

        // Update the new input state
        Input::Update();

        // Execute the physics update on all objects if needed
        PhysicsManager::Update(&scene);

        // Execute Update calls on each game object in the current scene
        scene.Update();

        CustomRun();

        // Render
        Renderer::Draw();
    }

    OnEnd();

    glfwTerminate();
}
