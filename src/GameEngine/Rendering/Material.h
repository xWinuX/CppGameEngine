#pragma once

#include "UniformBuffer.h"
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
                    Front = GL_BACK,
                    Back = GL_FRONT,
                    None = GL_FRONT_AND_BACK,
                };

                enum RenderMode
                {
                    Fill = GL_FILL,
                    Wireframe = GL_LINE
                };

                explicit Material(Shader* shader);
                ~Material();
                Shader*        GetShader() const;
                UniformBuffer* GetUniformBuffer() const;

                RenderMode GetRenderMode() const;
                CullFace   GetCullFace() const;
                bool GetTransparent() const;

                void SetRenderMode(RenderMode renderMode);
                void SetCullFace(CullFace cullFace);
                void SetTransparent(bool transparent);

            private:
                Shader*        _shader;
                UniformBuffer* _uniformBuffer;
                CullFace       _cullFace   = CullFace::None;
                RenderMode     _renderMode = RenderMode::Fill;
                bool _transparent = false;

        };
    }
}
