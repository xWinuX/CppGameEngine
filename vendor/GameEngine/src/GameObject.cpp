#include "GameEngine/GameObject.h"

#include <iostream>

#include "GameEngine/Debug/Log.h"

using namespace GameEngine::Debug;
using namespace GameEngine;


#define DO_FUNCTION(func) \
for (GameEngine::Components::Component* component : _components) \
{ \
    if (!component->GetEnabled()) { continue; } \
    component->func; \
} \
for (const GameObject* child : _children) { child->func; }

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
        i                       = _children.erase(i);
        delete child;
    }

    // Remove 
    if (_parent != nullptr) { _parent->RemoveChild(this); }
}

GameObject::GameObject(const glm::vec3 position) :
    GameObject() { _transform->SetLocalPosition(position); }

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

Layer GameObject::GetLayer() const { return _layer; }

void GameObject::SetParent(GameObject* newParent)
{
    if (newParent == nullptr) { Debug::Log::Message("Given Parent is null!"); }

    if (_parent != nullptr) { _parent->RemoveChild(this); }

    _parent = newParent;
    newParent->AddChild(this);
}

GameObject* GameObject::GetParent() const { return _parent; }
void        GameObject::SetLayer(Layer layer) { _layer = layer; }

void GameObject::OnStart() const { DO_FUNCTION(OnStart()) }
void GameObject::OnUpdateBegin() const { DO_FUNCTION(OnUpdateBegin()) }
void GameObject::OnPhysicsUpdate() const { DO_FUNCTION(OnPhysicsUpdate()) }
void GameObject::OnPhysicsUpdateEnd(const float interpolationFactor) const { DO_FUNCTION(OnPhysicsUpdateEnd(interpolationFactor)) }
void GameObject::OnUpdate() const { DO_FUNCTION(OnUpdate()) }
void GameObject::OnLateUpdate() const { DO_FUNCTION(OnLateUpdate()) }
void GameObject::OnUpdateEnd() const { DO_FUNCTION(OnUpdateEnd()) }
