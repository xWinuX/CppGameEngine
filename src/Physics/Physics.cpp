#include "Physics.h"

#include "../Core/Scene.h"
#include "../Utils/Time.h"

reactphysics3d::PhysicsCommon Physics::_physicsCommon;
reactphysics3d::PhysicsWorld* Physics::_physicsWorld     = Physics::_physicsCommon.createPhysicsWorld();
float                         Physics::_physicsTimeStep  = 1.0f / 60.0f;
float                         Physics::_frameAccumulator = 0.0f;

void Physics::Update(const GameEngine::Core::Scene* scene)
{
    _physicsWorld->setIsDebugRenderingEnabled(true);
    _physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
    _physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, true);
    _physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);

    const float deltaTime = std::min(Time::GetDeltaTime(), 0.25f);

    _frameAccumulator += deltaTime;

    // This executes the physics as many time as needed to catch up to real time again
    while (_frameAccumulator >= _physicsTimeStep)
    {
        scene->PhysicsUpdate();
        _physicsWorld->update(_physicsTimeStep);
        Debug::Log::Message("Physics Timestep");
        _frameAccumulator -= _physicsTimeStep;
    }
}

reactphysics3d::PhysicsWorld*    Physics::GetPhysicsWorld() { return _physicsWorld; }
reactphysics3d::PhysicsCommon*   Physics::GetPhysicsCommon() { return &_physicsCommon; }
reactphysics3d::MemoryAllocator& Physics::GetMemoryAllocator() { return _physicsWorld->getMemoryManager().getHeapAllocator(); }
