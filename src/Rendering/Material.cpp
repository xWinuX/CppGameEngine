#include "Material.h"
#include "Shader.h"

using namespace GameEngine::Rendering;

Material::Material(Shader* shader) :
    _shader(shader),
    _uniformBuffer(shader->GetUniformBufferCopy()) {}

Material::~Material() { delete _uniformBuffer; }

Shader*        Material::GetShader() const { return _shader; }
UniformBuffer* Material::GetUniformBuffer() const { return _uniformBuffer; }
