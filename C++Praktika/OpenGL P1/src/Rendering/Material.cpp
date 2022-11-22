#include "Material.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


Material::Material(Shader* shader) { _shader = shader; }

void Material::UseShader() const { _shader->Use(); }

void Material::ApplyUniforms() const
{
    for (const auto& uniform4F : _uniform4Fs)
    {
        Shader::SetUniform4F(uniform4F.first, uniform4F.second);
    }

    for (auto& uniformMat4F : _uniformMat4Fs)
    {
        Shader::SetUniformMat4F(uniformMat4F.first, uniformMat4F.second);
    }
}

void Material::SetUniform4F(const GLchar* uniformName, const Vector4 vector4)
{
    _uniform4Fs[_shader->GetUniformLocation(uniformName)] = vector4;
}

void Material::SetUniformMat4F(const GLchar* uniformName, const glm::mat4x4 mat4)
{
    _uniformMat4Fs[_shader->GetUniformLocation(uniformName)] = mat4;
}



Shader* Material::GetShader() const { return _shader; }
