#include "RainbowLight.h"

#include "GameEngine/Time.h"
#include "GameEngine/Utils/Math.h"

using namespace GameEngine;
using namespace GameEngine::Components;
using namespace GameEngine::Utils;

void RainbowLight::OnStart() { _pointLight = _gameObject->GetComponent<PointLight>(); }

void RainbowLight::OnUpdate()
{
    _pointLight->SetColor(glm::vec4(
                                    Math::Sin01(Time::GetTimeSinceStart() + 250),
                                    Math::Sin01(Time::GetTimeSinceStart() + 500),
                                    Math::Sin01(Time::GetTimeSinceStart() + 750),
                                    1.0f
                                   ));
}
