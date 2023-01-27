#pragma once

#include <reactphysics3d/engine/PhysicsCommon.h>

#include "GameEngine/Application.h"
#include "GameEngine/Scene.h"
#include "GameEngine/Rendering/Material.h"


namespace GameEngine
{
    namespace Physics
    {
        class PhysicsDebugRenderer;


        class PhysicsManager
        {
            friend Application;

            private:
                static reactphysics3d::PhysicsCommon              _physicsCommon;
                static reactphysics3d::PhysicsWorld*              _physicsWorld;
                static float                                      _physicsTimeStep;
                static float                                      _frameAccumulator;
                static bool                                       _renderDebugWireFrame;
                static GameEngine::Physics::PhysicsDebugRenderer* _debugRenderer;
                static GameEngine::Rendering::Material*           _debugMaterial;

                static void Update(const GameEngine::Scene* scene);

            public:
                static reactphysics3d::PhysicsWorld*    GetPhysicsWorld();
                static reactphysics3d::PhysicsCommon*   GetPhysicsCommon();
                static reactphysics3d::MemoryAllocator& GetMemoryAllocator();
                static void                             ToggleDebugWireframe();
                static void                             SetDebugRendererMaterial(Rendering::Material* material);
        };
    }
}
