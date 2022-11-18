#include "Material.h"
#include "Shader.h"

Material::Material(Shader* shader) { _shader = shader; }

void Material::UseShader() const { _shader->Use(); }

void Material::ApplyUniforms() const
{
    for (const auto& uniform4F : _uniform4Fs)
    {
        Shader::SetUniform4F(uniform4F.first, uniform4F.second);
    }
}

void Material::SetUniform4F(const GLchar* uniformName, const Vector4 vector4)
{
    _uniform4Fs[_shader->GetUniformLocation(uniformName)] = vector4;
}

Shader* Material::GetShader() const { return _shader; }
