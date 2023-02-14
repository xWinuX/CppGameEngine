﻿#include "GameEngine/Rendering/Material.h"

#include "GameEngine/Rendering/Shader.h"

using namespace GameEngine::Rendering;

Material::Material(std::string name, Shader* shader):
    _name(std::move(name)),
    _shader(shader),
    _uniformStorage(shader->GetUniformStorageCopy()) {}

Material::~Material() { delete _uniformStorage; }

Shader*              Material::GetShader() const { return _shader; }
UniformStorage*      Material::GetUniformStorage() const { return _uniformStorage; }
Material::RenderMode Material::GetRenderMode() const { return _renderMode; }
Material::CullFace   Material::GetCullFace() const { return _cullFace; }
Material::DepthFunc  Material::GetDepthFunc() const { return _depthFunc; }
void                 Material::SetDepthFunc(const DepthFunc depthFunc) { _depthFunc = depthFunc; }
bool                 Material::GetTransparent() const { return _transparent; }
void                 Material::SetTransparent(const bool transparent) { _transparent = transparent; }

void Material::DrawProperties() const
{
    if (ImGui::CollapsingHeader(_name.c_str())) { _uniformStorage->DrawProperties(_name); }
    ImGui::Spacing();
}

void Material::SetRenderMode(const RenderMode renderMode) { _renderMode = renderMode; }
void Material::SetCullFace(const CullFace cullFace) { _cullFace = cullFace; }