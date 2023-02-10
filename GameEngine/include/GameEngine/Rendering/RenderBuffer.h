﻿#pragma once
#include "glad/glad.h"
#include "glm/vec2.hpp"

class RenderBuffer
{
    private:
        GLuint _renderBufferID = 0;

    public:
        explicit RenderBuffer(const glm::uvec2 size, const GLenum format);
        ~RenderBuffer();
        void   Bind() const;
        void   Unbind() const; 
        GLuint GetRenderBufferId() const;
    
};