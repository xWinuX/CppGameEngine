#include "PhysicsManager.h"

#include "../Core/Scene.h"
#include "../Components/MeshRenderer.h"
#include "../Rendering/Renderer.h"
#include "PhysicsDebugRenderer.h"
#include "../Utils/Time.h"

using namespace GameEngine::Physics;
using namespace GameEngine::Rendering;
using namespace GameEngine::Core;
using namespace GameEngine::Components;

reactphysics3d::PhysicsCommon PhysicsManager::_physicsCommon;
reactphysics3d::PhysicsWorld* PhysicsManager::_physicsWorld  = PhysicsManager::_physicsCommon.createPhysicsWorld();
Material*                     PhysicsManager::_debugMaterial = nullptr;
PhysicsDebugRenderer*         PhysicsManager::_debugRenderer = nullptr;


float PhysicsManager::_physicsTimeStep      = 1.0f / 60.0f;
float PhysicsManager::_frameAccumulator     = 0.0f;
bool  PhysicsManager::_renderDebugWireFrame = false;

void PhysicsManager::Update(const GameEngine::Core::Scene* scene)
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

        Debug::Log::Message("Rendering physics debug");
        _debugRenderer->Render();
    }
    else
    {
        if (_debugRenderer != nullptr)
        {
            Debug::Log::Message("destroying physics debug renderer");
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

void PhysicsManager::SetDebugRendererMaterial(Rendering::Material* material)
{
    _debugMaterial = material;
    if (_debugRenderer != nullptr) { _debugRenderer->SetMaterial(_debugMaterial); }
}
