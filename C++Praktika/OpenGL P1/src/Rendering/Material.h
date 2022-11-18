#pragma once
#include <glad/glad.h>
#include "Shader.h"

class Material
{
    private:
        Shader*                   _shader;
        std::map<int, Vector4> _uniform4Fs;
    public:
        explicit Material(Shader* shader);
        void     UseShader() const;
        void     ApplyUniforms() const;
        void     SetUniform4F(const GLchar* uniformName, const Vector4 vector4);
        Shader*  GetShader() const;
};
