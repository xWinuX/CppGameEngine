﻿#include "GameEngine/Scene.h"

using namespace GameEngine;

Scene::~Scene() { delete _sceneRoot; }

void Scene::InitializeScene() const { _sceneRoot->OnStart(); }

void Scene::Update() const
{
    _sceneRoot->OnUpdateBegin();
    _sceneRoot->OnUpdate();
    _sceneRoot->OnLateUpdate();
    _sceneRoot->OnUpdateEnd();
}

void Scene::PhysicsUpdate() const { _sceneRoot->OnPhysicsUpdate(); }

void Scene::AddGameObject(GameObject* gameObject) const { gameObject->SetParent(_sceneRoot); }
