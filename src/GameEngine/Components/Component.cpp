﻿#include "Component.h"

using namespace GameEngine::Components;

GameEngine::Components::Component::Component():
    _gameObject(nullptr),
    _transform(nullptr) {}

void Component::OnStart() {}
void Component::OnUpdate() {}
void Component::OnPhysicsUpdate() {}
void Component::OnLateUpdate() {}
void Component::OnBeforeRender() {}
void Component::OnComponentAdded() {}
void Component::OnOtherComponentAdded(Component* component) {}
void Component::SetEnabled(const bool enabled) { _enabled = enabled; }

bool             Component::GetEnabled() const { return _enabled; }
const Transform* Component::GetTransform() const { return _transform; }