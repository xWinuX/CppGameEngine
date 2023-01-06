﻿#pragma once

#include "Component.h"
#include <reactphysics3d/body/RigidBody.h>

#include "reactphysics3d/components/RigidBodyComponents.h"


namespace GameEngine
{
    namespace Components
    {
        class Rigidbody : public Component
        {
            private:
                reactphysics3d::RigidBody* _pPhysicsRigidBody;
            public:
                explicit Rigidbody(reactphysics3d::BodyType bodyType = reactphysics3d::BodyType::DYNAMIC);
                ~Rigidbody() override;
                void OnStart() override;
                void OnPhysicsUpdate() override;
                void OnComponentAdded(Component* component) override;
        };
    }
}