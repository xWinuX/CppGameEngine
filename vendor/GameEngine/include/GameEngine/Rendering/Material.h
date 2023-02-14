#pragma once

#include "UniformStorage.h"
#include "glad/glad.h"

namespace GameEngine
{
    namespace Rendering
    {
        class Material
        {
            public:
                enum CullFace
                {
                    Front = GL_FRONT,
                    Back  = GL_BACK,
                    None  = 0,
                };

                enum RenderMode
                {
                    Fill      = GL_FILL,
                    Wireframe = GL_LINE
                };

                enum DepthFunc
                {
                    Equal   = GL_EQUAL,
                    LEqual  = GL_LEQUAL,
                    Less    = GL_LESS,
                    NoCheck = GL_ALWAYS,
                };

                explicit Material(std::string name, Shader* shader);
                ~Material();
                Shader*         GetShader() const;
                UniformStorage* GetUniformStorage() const;

                RenderMode GetRenderMode() const;
                CullFace   GetCullFace() const;
                DepthFunc  GetDepthFunc() const;
                bool       GetTransparent() const;

                void SetRenderMode(RenderMode renderMode);
                void SetCullFace(CullFace cullFace);
                void SetDepthFunc(DepthFunc depthFunc);
                void SetTransparent(bool transparent);
                void DrawProperties() const;

            private:
                std::string     _name;
                Shader*         _shader;
                UniformStorage* _uniformStorage;
                CullFace        _cullFace    = CullFace::Back;
                RenderMode      _renderMode  = RenderMode::Fill;
                DepthFunc       _depthFunc   = DepthFunc::Less;
                bool            _transparent = false;
        };
    }
}
