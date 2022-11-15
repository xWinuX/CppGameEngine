#pragma once
#include "Shader.h"

class Material
{
    private:
        const Shader* _shader;
    public:
        explicit Material(const Shader* shader);
        void UseShader() const;
};
