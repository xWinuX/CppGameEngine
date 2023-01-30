#pragma once
#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "glad/glad.h"

namespace GameEngine
{
    namespace Rendering
    {
        class FrameBuffer
        {
            private:
                GLuint _frameBufferID  = 0;
                GLuint _renderBufferID = 0;

                GameEngine::Rendering::Texture* _framebufferTexture = nullptr;
                VertexArrayObject*              _vertexArrayObject;

            public:
                explicit FrameBuffer();
                ~FrameBuffer();
                void Draw() const;
                void Bind() const;
                void Unbind();
        };
    }
}
