#pragma once

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
                reactphysics3d::RigidBody* _physicsRigidBody;
                reactphysics3d::Transform _previousTransform;
                float _mass = 1.0;
            protected:
                void OnStart() override;
                void OnPhysicsUpdateEnd(float interpolationFactor) override;
                void OnOtherComponentAdded(Component* component) override;
                void OnGuiDraw() override;

            public:
                explicit Rigidbody(reactphysics3d::BodyType bodyType = reactphysics3d::BodyType::DYNAMIC);
                ~Rigidbody() override;

                void      ResetForce() const;
                glm::vec3 GetVelocity() const;
                void      SetVelocity(glm::vec3 velocity) const;
                void      ApplyForce(glm::vec3 force) const;
                void      ApplyTorque(glm::vec3 torque) const;
                void      SetAngularVelocityLockAxisFactor(glm::vec3 lockAxis) const;
        };
    }
}
