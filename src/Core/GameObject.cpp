#include "GameObject.h"

#include <iostream>

GameObject::GameObject(): _transform(new TransformComponent()) { _components.push_back(_transform); }

GameObject::~GameObject()
{
    for (const Component* component : _components)
    {
        delete component;
    }
}

GameObject::GameObject(const glm::vec3 position) : GameObject() { _transform->SetPosition(position); }

std::vector<Component*>& GameObject::GetComponents() { return _components; }

void GameObject::AddComponent(Component* component)
{
    _components.push_back(component);
    component->SetTransform(_transform);
}

void GameObject::OnStart() const
{
    for (Component* component : _components) { component->OnStart(); }
}

void GameObject::OnUpdate() const
{
    for (Component* component : _components) { component->OnUpdate(); }
}

void GameObject::OnLateUpdate() const
{
    for (Component* component : _components) { component->OnLateUpdate(); }
}

void GameObject::OnBeforeRender() const
{
    for (Component* component : _components) { component->OnBeforeRender(); }
}