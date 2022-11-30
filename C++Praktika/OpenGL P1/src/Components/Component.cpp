#include "Component.h"

void Component::AttachToGameObject(GameObject* gameObject)
{
    _gameObject = gameObject;
}

Transform Component::GetTransform() const
{
    return _gameObject->GetTransform();
}
