#pragma once
#include "Component.h"
#include "../Rendering/Shader.h"

class Light : public Component
{
    protected:
        Shader* _shader;
    public:
        explicit Light(Shader* shader);
        void OnBeforeRender() override;
        virtual void OnShaderUse() = 0;    
};
