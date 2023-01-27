#pragma once

#include "../Core/Scene.h"
#include "../Rendering/Material.h"
#include "reactphysics3d/engine/PhysicsCommon.h"

namespace GameEngine
{
    namespace Physics
    {
        class PhysicsDebugRenderer;

        class Physics
        {
            private:
                static reactphysics3d::PhysicsCommon              _physicsCommon;
                static reactphysics3d::PhysicsWorld*              _physicsWorld;
                static float                                      _physicsTimeStep;
                static float                                      _frameAccumulator;
                static bool                                       _renderDebugWireFrame;
                static GameEngine::Physics::PhysicsDebugRenderer* _debugRenderer;
                static GameEngine::Rendering::Material*           _debugMaterial;

            public:
                static void                             Update(const GameEngine::Core::Scene* scene);
                static reactphysics3d::PhysicsWorld*    GetPhysicsWorld();
                static reactphysics3d::PhysicsCommon*   GetPhysicsCommon();
                static reactphysics3d::MemoryAllocator& GetMemoryAllocator();
                static void                             ToggleDebugWireframe();
                static void                             SetDebugRendererMaterial(Rendering::Material* material);
        };
    }
}
