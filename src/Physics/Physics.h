#pragma once
#include <vector>

#include "../Core/Scene.h"
#include "reactphysics3d/engine/PhysicsCommon.h"

class Physics
{
    private:
        static reactphysics3d::PhysicsCommon _physicsCommon;
        static reactphysics3d::PhysicsWorld* _physicsWorld;
        static float _physicsTimeStep;
        static float _frameAccumulator;
    public:
        static void Update(const GameEngine::Core::Scene* scene);
        static reactphysics3d::PhysicsWorld* GetPhysicsWorld();
        static reactphysics3d::PhysicsCommon* GetPhysicsCommon();
        static reactphysics3d::MemoryAllocator& GetMemoryAllocator();
};
