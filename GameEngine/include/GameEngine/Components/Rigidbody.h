﻿#pragma once

#include <reactphysics3d/body/RigidBody.h>

#include "Component.h"
#include "glm/vec3.hpp"
#include "reactphysics3d/components/RigidBodyComponents.h"


namespace GameEngine
{
    namespace Components
    {
        class Rigidbody : public Component
        {
            private:
                reactphysics3d::RigidBody* _pPhysicsRigidBody;

            protected:
                void OnStart() override;
                void OnPhysicsUpdate() override;
                void OnOtherComponentAdded(Component* component) override;

            public:
                explicit Rigidbody(reactphysics3d::BodyType bodyType = reactphysics3d::BodyType::DYNAMIC);
                ~Rigidbody() override;

                void ApplyForce(glm::vec3 force) const;
                void ApplyTorque(glm::vec3 torque) const;
        };
    }
}