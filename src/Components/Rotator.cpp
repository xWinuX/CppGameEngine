#include "Rotator.h"

#include "imgui.h"
#include "GameEngine/Time.h"
#include "GameEngine/Components/Transform.h"

using namespace GameEngine;

Rotator::Rotator():
    Component("Rotator") {}

void Rotator::OnUpdate() { _transform->Rotate(glm::vec3(0, _speed * Time::GetDeltaTime(), 0.0f)); }
void Rotator::OnGuiDraw()
{
    ImGui::SliderFloat(GetImGuiIDString("Rotation Speed").c_str(), &_speed, 0, 100);
}
