﻿#include "GameEngine/Rendering/RenderablePrimitive.h"

#include "GameEngine/Rendering/Shader.h"
#include "GameEngine/Rendering/VertexArrayObject.h"

using namespace GameEngine::Rendering;

RenderablePrimitive::RenderablePrimitive(Primitive* primitive, Material* material):
    _primitive(primitive),
    _material(material) {}

void RenderablePrimitive::OnBeforeDraw()
{
    if (_transform == nullptr) { return; }
    Shader::GetCurrentActiveShader()->GetUniformStorage()->SetUniformInstant<glm::mat4>("u_Transform", _transform->GetTRS());
}

void RenderablePrimitive::OnDraw()
{
    _primitive->GetVertexArrayObject()->Bind();
    _primitive->GetVertexArrayObject()->Draw();
    _primitive->GetVertexArrayObject()->Unbind();
}

Material* RenderablePrimitive::GetMaterial() { return _material; }
void      RenderablePrimitive::SetMaterial(Material* material) { _material = material; }
void      RenderablePrimitive::SetTransform(Components::Transform* transform) { _transform = transform; }