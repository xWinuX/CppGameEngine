#include "GameEngine/Physics/Physics.h"

#include <reactphysics3d/engine/PhysicsCommon.h>

#include "GameEngine/Physics/PhysicsDebugRenderer.h"
#include "GameEngine/Utils/Time.h"

using namespace GameEngine::Physics;
using namespace GameEngine::Rendering;
using namespace GameEngine::Core;
using namespace GameEngine::Components;

reactphysics3d::PhysicsCommon Physics::_physicsCommon;
reactphysics3d::PhysicsWorld* Physics::_physicsWorld  = Physics::_physicsCommon.createPhysicsWorld();
Material*                     Physics::_debugMaterial = nullptr;
PhysicsDebugRenderer*         Physics::_debugRenderer = nullptr;

float Physics::_physicsTimeStep      = 1.0f / 60.0f;
float Physics::_frameAccumulator     = 0.0f;
bool  Physics::_renderDebugWireFrame = false;

void Physics::Update(const GameEngine::Core::Scene* scene)
{
    const float deltaTime = std::min(Time::GetDeltaTime(), 0.25f);

    _frameAccumulator += deltaTime;

    // This executes the physics as many time as needed to catch up to real time again
    while (_frameAccumulator >= _physicsTimeStep)
    {
        scene->PhysicsUpdate();
        _physicsWorld->update(_physicsTimeStep);
        _frameAccumulator -= _physicsTimeStep;
    }

    if (_renderDebugWireFrame)
    {
        if (_debugRenderer == nullptr)
        {
            _debugRenderer = new PhysicsDebugRenderer();
            _debugRenderer->SetMaterial(_debugMaterial);
        }

        _debugRenderer->Render();
    }
    else
    {
        if (_debugRenderer != nullptr)
        {
            delete _debugRenderer;
            _debugRenderer = nullptr;
        }
    }
}

reactphysics3d::PhysicsWorld*    Physics::GetPhysicsWorld() { return _physicsWorld; }
reactphysics3d::PhysicsCommon*   Physics::GetPhysicsCommon() { return &_physicsCommon; }
reactphysics3d::MemoryAllocator& Physics::GetMemoryAllocator() { return _physicsWorld->getMemoryManager().getHeapAllocator(); }

void Physics::ToggleDebugWireframe()
{
    _renderDebugWireFrame = !_renderDebugWireFrame;


    Debug::Log::Message("Toggled physics debug is now: " + std::to_string(_renderDebugWireFrame));
}

void Physics::SetDebugRendererMaterial(Rendering::Material* material)
{
    _debugMaterial = material;
    if (_debugRenderer != nullptr) { _debugRenderer->SetMaterial(_debugMaterial); }
}
