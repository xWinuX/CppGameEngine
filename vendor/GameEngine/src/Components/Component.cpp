#include "GameEngine/Components/Component.h"

#include "imgui.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/Debug/Log.h"
#include "glm/gtc/type_ptr.hpp"

using namespace GameEngine::Components;

void Component::OnStart() {}
void Component::OnUpdateBegin() {}
void Component::OnUpdate() {}
void Component::OnLateUpdate() {}
void Component::OnPhysicsUpdate() {}
void Component::OnPhysicsUpdateEnd(float interpolationFactor) {}
void Component::OnUpdateEnd() {}
void Component::OnGuiDraw() { }
void Component::OnComponentAdded() {}
void Component::OnOtherComponentAdded(Component* component) {}

Component::Component(const std::string& name):
    _name(name),
    _gameObject(nullptr),
    _transform(nullptr) {}

std::string Component::GetImGuiName() const { return GetImGuiIDString(_name); }
void        Component::SetEnabled(const bool enabled) { _enabled = enabled; }

bool       Component::GetEnabled() const { return _enabled; }
bool       Component::GetInitialized() const { return _initialized; }
Transform* Component::GetTransform() const { return _transform; }

void Component::SetInitialized(const bool initialized) { _initialized = initialized; }
