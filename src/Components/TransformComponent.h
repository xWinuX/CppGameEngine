#pragma once
#include "../Core/Transform.h"
#include "Component.h"
namespace GameEngine
{
    namespace Components
    {
        class TransformComponent final : public Component, public Core::Transform {};
    }
}