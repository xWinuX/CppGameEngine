#include "Material.h"
#include "Shader.h"

using namespace GameEngine::Rendering;

Material::Material(Shader* shader) :
    _shader(shader),
    _uniformBuffer(shader->GetUniformBufferCopy()) {}

Material::~Material() { delete _uniformBuffer; }

Shader*              Material::GetShader() const { return _shader; }
UniformBuffer*       Material::GetUniformBuffer() const { return _uniformBuffer; }
Material::RenderMode Material::GetRenderMode() const { return _renderMode; }
Material::CullFace   Material::GetCullFace() const { return _cullFace; }
bool                 Material::GetTransparent() const { return _transparent; }
void                 Material::SetTransparent(const bool transparent) { _transparent = transparent; }

void Material::SetRenderMode(const RenderMode renderMode) { _renderMode = renderMode; }
void Material::SetCullFace(const CullFace cullFace) { _cullFace = cullFace; }
