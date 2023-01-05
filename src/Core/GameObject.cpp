#include "GameObject.h"

#include <iostream>

using namespace GameEngine::Core;

GameObject::GameObject():
    _transform(new GameEngine::Components::TransformComponent()) { _components.push_back(_transform); }

GameObject::~GameObject() { for (const GameEngine::Components::Component* component : _components) { delete component; } }

GameObject::GameObject(const glm::vec3 position) :
    GameObject() { _transform->SetPosition(position); }

std::vector<GameEngine::Components::Component*>& GameObject::GetComponents() { return _components; }

void GameObject::AddComponent(GameEngine::Components::Component* addedComponent)
{
    _components.push_back(addedComponent);
    addedComponent->_transform  = _transform;
    addedComponent->_gameObject = this;
    
    for (Components::Component* component : _components) { if (component != addedComponent) { component->OnComponentAdded(addedComponent); } }
}

void GameObject::OnStart() const { for (Components::Component* component : _components) { component->OnStart(); } }

void GameObject::OnPhysicsUpdate() const {for (GameEngine::Components::Component* component : _components) { component->OnPhysicsUpdate(); } }

void GameObject::OnUpdate() const { for (GameEngine::Components::Component* component : _components) { component->OnUpdate(); } }

void GameObject::OnLateUpdate() const { for (GameEngine::Components::Component* component : _components) { component->OnLateUpdate(); } }

void GameObject::OnBeforeRender() const { for (GameEngine::Components::Component* component : _components) { component->OnBeforeRender(); } }
