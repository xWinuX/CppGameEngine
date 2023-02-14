#include "GameEngine/Scene.h"

#include "GameEngine/GUIManager.h"
#include "GameEngine/Debug/Log.h"

using namespace GameEngine;

Scene* Scene::_currentScene = nullptr;

Scene::~Scene() { delete _sceneRoot; }
void Scene::Bind() { _currentScene = this; }

void Scene::OnUpdate()
{
    // Execute start event for all game object that haven't been started yet
    _sceneRoot->OnStart(); // Execute on start for uninitialized components
    _sceneRoot->OnUpdateBegin();
    _sceneRoot->OnUpdate();
    _sceneRoot->OnLateUpdate();
    _sceneRoot->OnUpdateEnd();

    if (!GUIManager::IsHidden()) { _sceneRoot->OnDrawGui(); }
}

void Scene::OnPhysicsUpdate() const { _sceneRoot->OnPhysicsUpdate(); }

void Scene::OnPhysicsUpdateEnd(const float interpolationFactor) const { _sceneRoot->OnPhysicsUpdateEnd(interpolationFactor); }

Scene* Scene::GetCurrentScene() { return _currentScene; }

void Scene::AddGameObject(GameObject* gameObject)
{
    if (_sceneRoot == nullptr)
    {
        Debug::Log::Message("scene root is null");
        return;
    }
    gameObject->SetParent(_sceneRoot);
    _uninitializedGameObjects.push_back(gameObject);
}

Scene::Scene()
{
    Bind();
    _sceneRoot = new GameObject("Scene Hierarchy");
}
