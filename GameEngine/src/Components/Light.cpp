﻿#include "GameEngine/Components/Light.h"

#include "GameEngine/Rendering/Renderer.h"

using namespace GameEngine::Components;
using namespace GameEngine::Rendering;


void Light::OnUpdateEnd() { Renderer::SubmitLight(this); }
