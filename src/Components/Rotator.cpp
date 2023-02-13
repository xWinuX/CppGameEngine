#include "Rotator.h"

#include "GameEngine/Time.h"
#include "GameEngine/Components/Transform.h"

using namespace GameEngine;

void Rotator::OnUpdate() { _transform->Rotate(glm::vec3(0, 20.0f * Time::GetDeltaTime(), 0.0f)); }
