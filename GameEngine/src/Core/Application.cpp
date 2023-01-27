#include "GameEngine/Core/Application.h"

#include <tiny_gltf.h>

#include "GameEngine/Input/Input.h"
#include "GameEngine/Physics/Physics.h"
#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Debug;
using namespace GameEngine::Core;
using namespace GameEngine::Rendering;
using namespace GameEngine::Physics;
using namespace GameEngine::Input;

bool cull = false;

Application::Application()
{
    glfwInit();

    _window.CreateContext();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) { Log::Error("Failed to initialize GLAD"); }

    Renderer::Initialize();

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
        Physics::Update(&scene);

        // Execute Update calls on each game object in the current scene
        scene.Update();

        CustomRun();

        // Render
        Renderer::Draw();
    }

    OnEnd();

    glfwTerminate();
}
