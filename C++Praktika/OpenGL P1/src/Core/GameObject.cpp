#include "GameObject.h"

GameObject::GameObject()
{
    _components.push_back(_transform);
}

GameObject::GameObject(const glm::vec3 position) : GameObject()
{
    _transform.SetPosition(position);
}

std::vector<Component>& GameObject::GetComponents()
{
    return _components;
}

void GameObject::Update()
{
    for (Component component : _components)
    {
        component.Update();
    }
}

void GameObject::LateUpdate()
{
    for (Component component : _components)
    {
        component.LateUpdate();
    }
}

void GameObject::Draw()
{
    for (Component component : _components)
    {
        component.Draw();
    }
}


