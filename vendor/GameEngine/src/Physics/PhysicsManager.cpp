#include "GameEngine/Physics/PhysicsManager.h"

#include <reactphysics3d/engine/PhysicsCommon.h>

#include "GameEngine/Physics/PhysicsDebugRenderer.h"
#include "GameEngine/Time.h"

using namespace GameEngine::Physics;
using namespace GameEngine::Rendering;
using namespace GameEngine::Components;

reactphysics3d::PhysicsCommon PhysicsManager::_physicsCommon;
reactphysics3d::PhysicsWorld* PhysicsManager::_physicsWorld  = nullptr;
Material*                     PhysicsManager::_debugMaterial = nullptr;
PhysicsDebugRenderer*         PhysicsManager::_debugRenderer = nullptr;

float PhysicsManager::_physicsTimeStep      = 1.0f / 60.0f;
float PhysicsManager::_frameAccumulator     = 0.0f;
bool  PhysicsManager::_renderDebugWireFrame = false;

void PhysicsManager::Initialize()
{
    reactphysics3d::PhysicsWorld::WorldSettings worldSettings;
    worldSettings.defaultBounciness = 0;

    _physicsWorld = PhysicsManager::_physicsCommon.createPhysicsWorld(worldSettings);
}

void PhysicsManager::Update(const Scene* scene)
{
    _frameAccumulator += Time::GetDeltaTime();

    // This executes the physics as many time as needed to catch up to real time again
    while (_frameAccumulator >= _physicsTimeStep)
    {
        scene->OnPhysicsUpdate();
        _physicsWorld->update(_physicsTimeStep);
        _frameAccumulator -= _physicsTimeStep;
    }

    const float interpolationFactor = _frameAccumulator / _physicsTimeStep;
    scene->OnPhysicsUpdateEnd(interpolationFactor);

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

reactphysics3d::PhysicsWorld*    PhysicsManager::GetPhysicsWorld() { return _physicsWorld; }
reactphysics3d::PhysicsCommon*   PhysicsManager::GetPhysicsCommon() { return &_physicsCommon; }
reactphysics3d::MemoryAllocator& PhysicsManager::GetMemoryAllocator() { return _physicsWorld->getMemoryManager().getHeapAllocator(); }

void PhysicsManager::ToggleDebugWireframe()
{
    _renderDebugWireFrame = !_renderDebugWireFrame;


    Debug::Log::Message("Toggled physics debug is now: " + std::to_string(_renderDebugWireFrame));
}

float PhysicsManager::GetPhysicsTimeStep() { return _physicsTimeStep; }

void PhysicsManager::SetDebugRendererMaterial(Rendering::Material* material)
{
    _debugMaterial = material;
    if (_debugRenderer != nullptr) { _debugRenderer->SetMaterial(_debugMaterial); }
}
