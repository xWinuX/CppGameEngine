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

    for (const auto& uniformMat4F : _uniformMat4Fs)
    {
        Shader::SetUniformMat4F(uniformMat4F.first, uniformMat4F.second);
    }

    for (const auto& uniform1I : _uniform1Is)
    {
        Shader::SetUniformI1(uniform1I.first, uniform1I.second);
    }

    int i = 0;
    for (const auto& uniformTextureSamples2D : _uniformTextureSamples2Ds)
    {
        uniformTextureSamples2D.second->Bind(i);
        Shader::SetUniformI1(uniformTextureSamples2D.first, i);
        i++;
    }
}

void Material::SetUniform4F(const GLchar* uniformName, const glm::vec4 vector4) { _uniform4Fs[_shader->GetUniformLocation(uniformName)] = vector4; }

void Material::SetUniformMat4F(const GLchar* uniformName, const glm::mat4x4 mat4) { _uniformMat4Fs[_shader->GetUniformLocation(uniformName)] = mat4; }

void Material::SetUniformMat1I(const GLchar* uniformName, const int i) { _uniform1Is[_shader->GetUniformLocation(uniformName)] = i; }

void Material::SetUniformTextureSampler2D(const GLchar* uniformName, Texture* texture) { _uniformTextureSamples2Ds[_shader->GetUniformLocation(uniformName)] = texture; }

Shader* Material::GetShader() const { return _shader; }
