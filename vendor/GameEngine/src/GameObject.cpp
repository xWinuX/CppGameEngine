#include "GameEngine/GameObject.h"

#include <iostream>

#include "imgui.h"
#include "GameEngine/Scene.h"
#include "GameEngine/Debug/Log.h"

using namespace GameEngine::Debug;
using namespace GameEngine;


#define DO_FUNCTION(func) \
for (GameEngine::Components::Component* component : _components) \
{ \
    if (!component->GetEnabled() || !component->GetInitialized()) { continue; } \
    component->func; \
} \
for (const GameObject* child : _children) { child->func; }

GameObject::GameObject(const std::string& name):
    _name(name),
    _transform(new GameEngine::Components::Transform())
{
    AddComponent(_transform);
    Scene::GetCurrentScene()->AddGameObject(this);
}

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

    _uninitializedComponents.push_back(addedComponent);
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
void        GameObject::SetLayer(const Layer layer) { _layer = layer; }

void GameObject::OnStart()
{
    if (!_uninitializedComponents.empty())
    {
        for (GameEngine::Components::Component* component : _uninitializedComponents)
        {
            if (!component->GetEnabled()) { continue; }
            component->OnStart();
            component->SetInitialized(true);
        }
        _uninitializedComponents.clear();
    }

    for (GameObject* child : _children) { child->OnStart(); }
}

void GameObject::OnUpdateBegin() const { DO_FUNCTION(OnUpdateBegin()) }
void GameObject::OnPhysicsUpdate() const { DO_FUNCTION(OnPhysicsUpdate()) }
void GameObject::OnPhysicsUpdateEnd(const float interpolationFactor) const { DO_FUNCTION(OnPhysicsUpdateEnd(interpolationFactor)) }
void GameObject::OnUpdate() const { DO_FUNCTION(OnUpdate()) }
void GameObject::OnLateUpdate() const { DO_FUNCTION(OnLateUpdate()) }
void GameObject::OnUpdateEnd() const { DO_FUNCTION(OnUpdateEnd()) }

void GameObject::OnDrawGui() const
{
    if (ImGui::CollapsingHeader(GetImGuiIDString("OBJ: " + _name).c_str()))
    {
        ImGui::Indent();
        for (Components::Component* component : _components)
        {
            // Draw Properties
            if (ImGui::CollapsingHeader(component->GetImGuiName().c_str())) { component->OnGuiDraw(); }
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Indent();
        for (const GameObject* child : _children) { child->OnDrawGui(); }

        ImGui::Unindent();
        ImGui::Unindent();

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
    }
}
