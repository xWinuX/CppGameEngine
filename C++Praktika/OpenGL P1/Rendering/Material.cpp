#include "Material.h"
#include "Shader.h"

Material::Material(const Shader* shader) { _shader = shader;}

void Material::UseShader() const
{
    _shader->Use();
}
