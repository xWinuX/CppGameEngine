#pragma once
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

#include "Shader.h"
#include "Texture.h"

class Material
{
    private:
        Shader*                    _shader;
        std::map<int, glm::vec4>   _uniform4Fs;
        std::map<int, glm::mat4x4> _uniformMat4Fs;
        std::map<int, int>         _uniform1Is;
        std::map<int, Texture*>    _uniformTextureSamples2Ds;
    public:
        explicit Material(Shader* shader);
        void     UseShader() const;
        void     ApplyUniforms() const;
        void     SetUniform4F(const GLchar* uniformName, const glm::vec4 vector4);
        void     SetUniformMat4F(const GLchar* uniformName, glm::mat4x4 mat4);
        void     SetUniformMat1I(const GLchar* uniformName, int i);
        void     SetUniformTextureSampler2D(const GLchar* uniformName, Texture* texture);
        Shader*  GetShader() const;
};
