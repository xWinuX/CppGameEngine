#include "GameObject.h"

GameObject::GameObject() { _components.push_back(_transform); }

GameObject::GameObject(const glm::vec3 position) : GameObject() { _transform.SetPosition(position); }

std::vector<Component>& GameObject::GetComponents() { return _components; }

void GameObject::AddComponent(Component& component)
{
    _components.push_back(component);
    component.SetTransform(&_transform);
}

void GameObject::Update() const
{
    for (Component component : _components)
    {
        component.OnUpdate();
    }
}

void GameObject::LateUpdate() const
{
    for (Component component : _components)
    {
        component.OnLateUpdate();
    }
}

void GameObject::Draw() const
{
    for (Component component : _components)
    {
        component.OnDraw();
    }
}


