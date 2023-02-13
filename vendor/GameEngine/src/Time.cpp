#include "GameEngine/Time.h"

#include <GLFW/glfw3.h>

#include "GameEngine/Physics/PhysicsDebugRenderer.h"

using namespace GameEngine;

float Time::_deltaTime              = 0;
float Time::_previousTimeSinceStart = 0;

void Time::Update()
{
    const float newTime     = GetTimeSinceStart();
    Time::_deltaTime        = newTime - _previousTimeSinceStart;
    _previousTimeSinceStart = newTime;
}

float Time::GetDeltaTime() { return _deltaTime; }
float Time::GetPhysicsDeltaTime() { return Physics::PhysicsManager::GetPhysicsTimeStep(); }

float Time::GetTimeSinceStart() { return static_cast<float>(glfwGetTime()); }
