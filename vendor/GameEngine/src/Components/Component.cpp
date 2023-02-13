#include "GameEngine/Components/Component.h"

using namespace GameEngine::Components;

GameEngine::Components::Component::Component():
    _gameObject(nullptr),
    _transform(nullptr) {}

void Component::OnStart() {}
void Component::OnUpdateBegin() {}
void Component::OnUpdate() {}
void Component::OnLateUpdate() {}
void Component::OnPhysicsUpdate() {}
void Component::OnPhysicsUpdateEnd(float interpolationFactor) {}
void Component::OnUpdateEnd() {}
void Component::OnComponentAdded() {}
void Component::OnOtherComponentAdded(Component* component) {}
void Component::SetEnabled(const bool enabled) { _enabled = enabled; }

bool       Component::GetEnabled() const { return _enabled; }
Transform* Component::GetTransform() const { return _transform; }
