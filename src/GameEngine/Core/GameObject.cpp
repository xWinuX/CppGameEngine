#include "GameObject.h"

#include <iostream>

#include "../Debug/Log.h"

using namespace GameEngine::Debug;
using namespace GameEngine::Core;

GameObject::GameObject():
    _transform(new GameEngine::Components::Transform()) { AddComponent(_transform); }

GameObject::~GameObject()
{
    // Delete all components
    for (const GameEngine::Components::Component* component : _components) { delete component; }

    // Delete all children
    std::list<GameObject*>::iterator i = _children.begin();
    while (i != _children.end())
    {
        const GameObject* child = *i;
        i = _children.erase(i);
        delete child;
    }

    // Remove 
    if (_parent != nullptr) { _parent->RemoveChild(this); }
}

GameObject::GameObject(const glm::vec3 position) :
    GameObject() { _transform->SetPosition(position); }

std::vector<GameEngine::Components::Component*>& GameObject::GetComponents() { return _components; }

void GameObject::AddComponent(GameEngine::Components::Component* addedComponent)
{
    _components.push_back(addedComponent);
    addedComponent->_transform  = _transform;
    addedComponent->_gameObject = this;

    for (Components::Component* component : _components)
    {
        if (component == addedComponent) { component->OnComponentAdded(); }
        else { component->OnOtherComponentAdded(addedComponent); }
    }
}

void GameObject::AddChild(GameObject* child) { _children.push_back(child); }

void GameObject::RemoveChild(GameObject* child) { _children.remove(child); }

void GameObject::SetParent(GameObject* newParent)
{
    if (newParent == nullptr) { Debug::Log::Message("Given Parent is null!"); }

    if (_parent != nullptr) { _parent->RemoveChild(this); }

    _parent = newParent;
    newParent->AddChild(this);
}

GameObject* GameObject::GetParent() const { return _parent; }

void GameObject::OnStart() const
{
    for (Components::Component* component : _components) { component->OnStart(); }
    for (const GameObject* child : _children) { child->OnStart(); }
}

void GameObject::OnPhysicsUpdate() const
{
    for (GameEngine::Components::Component* component : _components)
    {
        if (!component->GetEnabled()) { continue; }
        component->OnPhysicsUpdate();
    }
    for (const GameObject* child : _children) { child->OnPhysicsUpdate(); }
}

void GameObject::OnUpdate() const
{
    for (GameEngine::Components::Component* component : _components)
    {
        if (!component->GetEnabled()) { continue; }
        component->OnUpdate();
    }
    for (const GameObject* child : _children) { child->OnUpdate(); }
}

void GameObject::OnLateUpdate() const
{
    for (GameEngine::Components::Component* component : _components)
    {
        if (!component->GetEnabled()) { continue; }
        component->OnLateUpdate();
    }
    for (const GameObject* child : _children) { child->OnLateUpdate(); }
}

void GameObject::OnBeforeRender() const
{
    for (GameEngine::Components::Component* component : _components)
    {
        if (!component->GetEnabled()) { continue; }
        component->OnBeforeRender();
    }
    for (const GameObject* child : _children) { child->OnBeforeRender(); }
}
